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
				fd = open(filename, O_WRONLY | O_CREAT, 0744);
				if (fd < 0)
					exit(1);
				close(fd);
			}
		}
		i = 0;
		rd = rd->next->next;
	}
	return ;
}

int	exec_builtin(t_inst *proc, t_env **envs)
{
	if (ft_strcmp(proc->inst, "cd") == 0)
		ft_cd(proc, *envs, *envs);
	else if (ft_strcmp(proc->inst, "echo") == 0)
		ft_echo(proc, proc->option);
	else if (ft_strcmp(proc->inst, "env") == 0)
		ft_env(*envs);
	else if (ft_strcmp(proc->inst, "exit") == 0)
		ft_exit(proc);
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

void	exec_child_process(t_inst *proc, t_inst *child, t_env **envs)
{
	int		ret;
	char	*path;
	char	**chunked[2];

	chunked[0] = inst_to_chunks(proc);
	chunked[1] = envs_to_chunks(*envs);
	ret = 0;
	path = get_path(proc->inst, *envs);
	printf("exec_child\n");
	if (proc->child != NULL)
		dup2(child->fds[1], STDOUT_FILENO);
	if (proc->fds[0] != 0)
	{
		dup2(proc->fds[0], STDIN_FILENO);
		close(proc->fds[0]);
	}
	if (exec_builtin(proc, envs))
		(ret = execve(path, chunked[0], chunked[1]));
	if (ret == -1)
		exec_error_handle(proc->inst, "command not found", 127);
	exit(0);
}

void	exec_pipe(t_inst *proc, t_env **envs)
{
	t_inst	*child;
	pid_t	pid;
	int		state;

	child = proc;
	if (proc->child != NULL)
	{
		child = proc->child;
		pipe(child->fds);
	}
	if (proc->rd)
	{
		redir_init(proc, envs);
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_child_process(proc, child, envs);
	waitpid(pid, &state, 0);
	if (proc->child)
		close(child->fds[1]);
}

void	exec_parent_process(t_inst *proc, t_env **envs)
{
	t_inst	*cur;

	cur = proc;
	while (cur != NULL)
	{
		if (cur->inst)
		{
			if (cur->child || (!(cur->rd) && exec_builtin(cur, envs)))
			{
				printf("here1\n");
				exec_pipe(cur, envs);
				while (cur->child)
				{
					cur = cur->child;
					exec_pipe(cur, envs);
				}
			}
			else if (cur->rd)
			{
				printf("here2\n");
				redir_init(cur, envs);
			}
		}
		else if (cur->rd && cur->rd->next)
			no_inst_redir(cur->rd);
		proc = proc->next;
		cur = proc;
	}
}
