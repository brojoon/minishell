#include "minishell.h"

int	exec_redir_right(t_inst *proc, t_env **envs)
{
	int		fds[2];
	char	*path;
	char	*filename;
	int		ret;
	char	**chunked[2];

	chunked[0] = inst_to_chunks(proc);
	chunked[1] = envs_to_chunks(*envs);
	filename = proc->rd->next->str;
	fds[0] = get_redir_fd(proc, 1);
	if (fds[0] == 0 || fds[0] == 1 || fds[0] == 2)
	{
		fds[1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0744);
		if (fds[1] < 0)
			exit(1);
		if (proc->fds[1] != 0)
		{
			dup2(proc->fds[0], STDIN_FILENO);
			close(proc->fds[0]);
		}
		dup2(fds[1], fds[0]);
		path = get_path(proc->inst, *envs);
		if (exec_builtin(proc, envs))
			ret = execve(path, chunked[0], chunked[1]);
		if (ret == -1)
			exit(1);
	}
	exit(0);
}

int	exec_redir_dright(t_inst *proc, t_env **envs)
{
	int		fds[2];
	char	*path;
	char	*filename;
	int		ret;
	char	**chunked[2];

	chunked[0] = inst_to_chunks(proc);
	chunked[1] = envs_to_chunks(*envs);

	filename = proc->rd->next->str;
	fds[0] = get_redir_fd(proc, 1);
	if (fds[0] == 0 || fds[0] == 1 || fds[0] == 2)
	{
		fds[1] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0744);
		if (fds[1] < 0)
			exit(1);
		if (proc->fds[1] != 0)
		{
			dup2(proc->fds[0], STDIN_FILENO);
			close(proc->fds[0]);
		}
		dup2(fds[1], fds[0]);
		close(fds[1]);
		path = get_path(proc->inst, *envs);
		if (exec_builtin(proc, envs))
			ret = execve(path, chunked[0], chunked[1]);
	}
	if (ret == -1)
	{
		catch_error(proc->inst, "command not found");
		exit(1);
	}
	exit(0);
}

void	exec_redir_left(t_inst *proc, t_env **envs)
{ 
	int		fd;
	char	*path;
	char	*filename;
	int		ret;
	char	**chunked[2];

	chunked[0] = inst_to_chunks(proc);
	chunked[1] = envs_to_chunks(*envs);
	filename = proc->rd->next->str;
	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
	{
		catch_error(filename, "No such file or directory");
		g_status = 1;
		exit (1);
	}
	dup2(fd, STDIN_FILENO);
	if (proc->child)
		dup2(STDOUT_FILENO, proc->child->fds[1]);
	path = get_path(proc->inst, *envs);
	if (exec_builtin(proc, envs))
		ret = execve(path, chunked[0], chunked[1]);      
	if (ret == -1)
	{
		catch_error(proc->inst, "command not found");
		g_status = 1;
		exit(1);
	}
	g_status = 0;
	exit(0);
}

void	redir_exec(t_inst *proc, t_env **envs)
{
	int		type;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		type = get_redir_type(proc->rd);
		if (type == RIGHT)
			exec_redir_right(proc, envs);
		else if (type == DRIGHT)
			exec_redir_dright(proc, envs);
		else if (type == LEFT)
			exec_redir_left(proc, envs);
	}
	wait(&g_status);
	if (proc->child)
		close(proc->child->fds[1]);
}

void	redir_init(t_inst *proc, t_env **envs)
{
	int	ret;

	while (proc->rd && proc->rd->next)
	{
		printf("redir\n");
		while (proc->rd != NULL && proc->rd->next 
				&& proc->rd->next->next && proc->rd->next->next->next \
				&& !ft_strcmp(proc->rd->str, proc->rd->next->next->str))
		{
			if (get_redir_type(proc->rd) == RIGHT || \
				get_redir_type(proc->rd) == DRIGHT)
					ret = redir_skip_right(proc->rd->next->str);
			else if (get_redir_type(proc->rd) == LEFT)
				ret = redir_skip_left(proc->rd->next->str);
			if (ret == -1)
				return;
			proc->rd = proc->rd->next->next;
			printf("hehe\n");
		}
		printf("redir_exec\n");
		redir_exec(proc, envs);
		proc->rd = proc->rd->next->next;
	}
}
