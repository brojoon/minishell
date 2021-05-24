/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:21:06 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 13:40:26 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_redir_right(t_inst *proc, t_env **envs, t_cursor *cursor, \
t_string *rd)
{
	int		fds[2];
	char	*path;
	int		ret;
	char	**chunked[2];

	chunked[0] = inst_to_chunks(proc);
	chunked[1] = envs_to_chunks(*envs);
	fds[0] = get_redir_fd(rd, 1);
	fds[1] = open(rd->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0744);
	if (fds[1] < 0)
		exit(1);
	if (proc->fds[1] != 0)
	{
		dup2(proc->fds[0], STDIN_FILENO);
		close(proc->fds[0]);
	}
	ret = 0;
	dup2(fds[1], fds[0]);
	path = get_path(proc->inst, *envs);
	if (exec_builtin(proc, envs, cursor))
		ret = execve(path, chunked[0], chunked[1]);
	if (ret == -1)
		exec_error_handle(proc->inst, ERR_CNF, 1);
	exit_status(g_status);
}

void	exec_redir_dright(t_inst *proc, t_env **envs, t_cursor *cursor, \
t_string *rd)
{
	int		fds[2];
	char	*path;
	int		ret;
	char	**chunked[2];

	chunked[0] = inst_to_chunks(proc);
	chunked[1] = envs_to_chunks(*envs);
	fds[0] = get_redir_fd(rd, 1);
	fds[1] = open(rd->next->str, O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (fds[1] < 0)
		exit(1);
	if (proc->fds[1] != 0)
	{
		dup2(proc->fds[0], STDIN_FILENO);
		close(proc->fds[0]);
	}
	dup2(fds[1], fds[0]);
	path = get_path(proc->inst, *envs);
	ret = 0;
	if (exec_builtin(proc, envs, cursor))
		ret = execve(path, chunked[0], chunked[1]);
	if (ret == -1)
		exec_error_handle(proc->inst, ERR_CNF, 1);
	exit_status(g_status);
}

void	exec_redir_left(t_inst *proc, t_env **envs, t_cursor *cursor, \
t_string *rd)
{
	int		fds[2];
	char	*path;
	char	*filename;
	int		ret;
	char	**chunked[2];

	chunked[0] = inst_to_chunks(proc);
	chunked[1] = envs_to_chunks(*envs);
	filename = rd->next->str;
	fds[0] = get_redir_fd(rd, 0);
	fds[1] = open(filename, O_RDONLY, 0644);
	if (fds[1] < 0)
		exec_error_handle(filename, ERR_NSFOD, 2);
	dup2(fds[1], fds[0]);
	if (proc->child)
		dup2(STDOUT_FILENO, proc->child->fds[1]);
	path = get_path(proc->inst, *envs);
	ret = 0;
	if (exec_builtin(proc, envs, cursor))
		ret = execve(path, chunked[0], chunked[1]);
	if (ret == -1)
		exec_error_handle(proc->inst, ERR_CNF, 1);
	exit_status(g_status);
}

void	redir_exec(t_inst *proc, t_env **envs, t_cursor *cursor, t_string *rd)
{
	int		type;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		type = get_redir_type(rd);
		if (type == RIGHT)
			exec_redir_right(proc, envs, cursor, rd);
		else if (type == DRIGHT)
			exec_redir_dright(proc, envs, cursor, rd);
		else if (type == LEFT)
			exec_redir_left(proc, envs, cursor, rd);
	}
	waitpid(pid, &g_status, 0);
	set_g_status();
	if (proc->child)
		close(proc->child->fds[1]);
}

void	redir_init(t_inst *proc, t_env **envs, t_cursor *cursor)
{
	int			ret;
	t_string	*rd;

	rd = proc->rd;
	ret = 0;
	while (rd && rd->next)
	{
		while (rd != NULL && rd->next
			&& rd->next->next && rd->next->next->next \
			&& !ft_strcmp(rd->str, rd->next->next->str))
		{
			if (get_redir_type(rd) == RIGHT || \
				get_redir_type(rd) == DRIGHT)
				ret = redir_skip_right(rd->next->str);
			else if (get_redir_type(rd) == LEFT)
				ret = redir_skip_left(rd->next->str);
			if (ret == -1)
				return ;
			rd = rd->next->next;
		}
		redir_exec(proc, envs, cursor, rd);
		rd = rd->next->next;
	}
}
