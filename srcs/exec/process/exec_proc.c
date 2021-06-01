/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:03:47 by hyungjki          #+#    #+#             */
/*   Updated: 2021/06/01 08:48:41 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_inst_redir(t_string *rd)
{
	int		i;
	int		fd;
	char	*filename;

	i = 0;
	while (rd && rd->next)
	{
		while (ft_isdigit(rd->str[i]))
			i++;
		if (rd->str[i] == '>')
		{
			if (rd->str[i + 1] == '>' || rd->str[i + 1] == '\0')
			{
				filename = rd->next->str;
				fd = open(filename, O_WRONLY | O_CREAT, 0644);
				if (fd < 0)
					exit(1);
				close(fd);
			}
		}
		i = 0;
		rd = rd->next->next;
	}
	g_bash.status = 0;
}

int		exec_builtin(t_inst *proc, t_env **envs, t_cursor *cursor)
{
	if (ft_strcmp(proc->inst, "cd") == 0)
		ft_cd(proc, *envs, *envs);
	else if (ft_strcmp(proc->inst, "echo") == 0)
		ft_echo(proc, proc->option);
	else if (ft_strcmp(proc->inst, "env") == 0)
		ft_env(*envs);
	else if (ft_strcmp(proc->inst, "exit") == 0)
		ft_exit(proc, cursor);
	else if (ft_strcmp(proc->inst, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(proc->inst, "unset") == 0)
		ft_unset(proc, envs);
	else if (ft_strcmp(proc->inst, "export") == 0)
		ft_export(proc, *envs);
	else if (ft_strcmp(proc->inst, "$?") == 0)
		print_status();
	else
		return (1);
	return (0);
}

void	child_process(t_inst *proc, t_inst *child, \
t_env **envs, t_cursor *cursor)
{
	int		ret;
	char	*path;
	char	**chunked[2];

	chunked[0] = inst_to_chunks(proc);
	chunked[1] = envs_to_chunks(*envs);
	ret = 0;
	path = get_path(proc->inst, *envs);
	if (proc->child != NULL)
	{
		dup2(child->fds[1], STDOUT_FILENO);
		close(child->fds[1]);
	}
	if (proc->fds[0] != 0)
	{
		dup2(proc->fds[0], STDIN_FILENO);
		close(proc->fds[0]);
	}
	if (exec_builtin(proc, envs, cursor))
		(ret = execve_before_term(path, chunked[0], chunked[1], cursor));
	if (ret == -1)
		exec_error_handle(proc->inst, ERR_CNF, 1);
	exit_status(g_bash.status);
}

void	exec_pipe(t_inst *proc, t_env **envs, t_cursor *cursor)
{
	t_inst	*child;
	pid_t	pid;

	child = proc;
	if (proc->child != NULL)
	{
		child = proc->child;
		pipe(child->fds);
	}
	if (proc->rd)
	{
		redir_init(proc, envs, cursor);
		return ;
	}
	pid = fork();
	if (pid == 0)
		child_process(proc, child, envs, cursor);
	waitpid(pid, &g_bash.status, 0);
	set_g_status();
	if (proc->child)
		close(child->fds[1]);
	if (proc->fds && proc->fds[0] != 0)
		close(proc->fds[0]);
}

void	exec_parent_process(t_inst *proc, t_env **envs, t_cursor *cursor)
{
	t_inst	*cur;

	cur = proc;
	while (cur != NULL)
	{
		if (cur->inst)
		{
			if (cur->child || (!(cur->rd) && exec_builtin(cur, envs, cursor)))
			{
				exec_pipe(cur, envs, cursor);
				while (cur->child)
				{
					cur = cur->child;
					exec_pipe(cur, envs, cursor);
				}
			}
			else if (cur->rd)
				redir_init(cur, envs, cursor);
		}
		else if (cur->rd && cur->rd->next)
			no_inst_redir(cur->rd);
		proc = proc->next;
		cur = proc;
	}
}
