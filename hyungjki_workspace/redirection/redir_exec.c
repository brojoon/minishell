#include "../minishell.h"

int exec_redir_right(t_inst *proc, t_env *g_env)
{
	int fds[2];
	char *path;
	char *filename;
	
	filename = ft_strchr(proc->rd->str, ">") + 1;
	while (*filename == ' ')
		filename++; 
	fds[0] = get_redir_fd(proc, 1);
	if (fds[0] == 0 || fds[0] == 1 || fds[0] == 2)
	{
		fds[1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0744);
		if (fds[1] < 0)
			exit(1);
		dup2(fds[1], fds[0]);
		close(fds[1]);
		path = get_path(proc->inst, g_env);
		if(exec_builtin(proc, g_env))
			//ret = execve(path, argv, g_envp);
	}
	else
		exit(1);
}

int exec_redir_dright(t_inst *proc, t_env *g_env)
{
	int fds[2];
	char *path;
	char *filename;

	filename = ft_strchr(proc->rd->str, ">") + 2;
	while (*filename == ' ')
		filename++; 
	fds[0] = get_redir_fd(proc, 1);
	if (fds[0] == 0 || fds[0] == 1 || fds[0] == 2)
	{
		fds[1] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0744);
		if (fds[1] < 0)
			exit(1);
		dup2(fds[1], fds[0]);
		close(fds[1]);
		path = get_path(proc->inst, g_env);
		if(exec_builtin(proc, g_env))
			//execve(path, argv, g_envp);
	}
	else
		exit(1);
}

int	exec_redir_left(t_inst *proc, t_env *g_env)
{
	int fd;
	char *path;
	char *filename;
	
	filename = ft_strchr(proc->rd->str, "<") + 1;
	while (*filename == ' ')
		filename++; 
	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
		exit(1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	path = get_path(proc->inst, g_env);
	if(exec_builtin(proc, g_env))
		//execve(path, argv, g_envp);
	free(path);
}

void redir_exec(t_inst *proc, t_env *g_env)
{
	int type;
	pid_t pid;
	int ret;
	int status;

	pid = fork();
	if (pid == 0)
	{
		type = get_redir_type(proc->rd);
		if (type == RIGHT)
			ret = exec_redir_right(proc, g_env);
		else if (type == DRIGHT)
			ret = exec_redir_dright(proc, g_env);
		else if (type == LEFT)
			ret = exec_redir_left(proc, g_env);
		exit(ret);
	}
	wait(&status);
}

void redir_init(t_inst *proc, t_env *g_env)
{
	char *filename;
	int ret;

	while (proc->rd->next != NULL)
	{
		if (get_redir_type(proc->rd->str) == RIGHT || \
			get_redir_type(proc->rd->str) == DRIGHT)
			ret = redir_skip_right(proc->rd->str);
		else if (get_redir_type(proc->rd->str) == LEFT)
			ret = redir_skip_left(proc->rd->str);
		if (ret == -1)
			return;
		proc->rd->next;
	}
	redir_exec(proc, g_env);
}