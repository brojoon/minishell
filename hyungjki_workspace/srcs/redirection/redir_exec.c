#include "../../includes/minishell.h"

int exec_redir_right(t_inst *proc, t_env *g_env)
{
	int fds[2];
	char *path;
	char *filename;
	char **argv;
	char **envs;
	int ret;
	
	envs = envs_to_chunks(g_env);
	argv = inst_to_chunks(proc);
	filename = proc->rd->next->str;
	fds[0] = get_redir_fd(proc, 1);
	if (fds[0] == 0 || fds[0] == 1 || fds[0] == 2)
	{
		fds[1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0744);
		if (fds[1] < 0)
			exit(1);
		dup2(fds[1], fds[0]);
		path = get_path(proc->inst, g_env);
		if(exec_builtin(proc, g_env))
			ret = execve(path, argv, envs);
	}
	exit(ret);
}

int exec_redir_dright(t_inst *proc, t_env *g_env)
{
	int fds[2];
	char *path;
	char *filename;
	char **argv;
	char **envs;
	int ret;
	
	envs = envs_to_chunks(g_env);
	argv = inst_to_chunks(proc);

	filename = proc->rd->next->str;
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
			ret = execve(path, argv, envs);
	}
	exit(ret);
}

int	exec_redir_left(t_inst *proc, t_env *g_env)
{
	int fd;
	char *path;
	char *filename;
	char **argv;
	char **envs;
	int ret;

	envs = envs_to_chunks(g_env);
	argv = inst_to_chunks(proc);
	
	filename = proc->rd->next->str;;
	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
		exit(1);
	dup2(fd, STDIN_FILENO);
	path = get_path(proc->inst, g_env);
	if(exec_builtin(proc, g_env))
		ret = execve(path, argv, envs);
	free(path);
	exit(ret);
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
		printf("1\n");
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
	int ret;

	while (proc->rd != NULL && proc->rd->next && proc->rd->next->next && proc->rd->next->next->next)
	{
		if (get_redir_type(proc->rd) == RIGHT || \
			get_redir_type(proc->rd) == DRIGHT)
				ret = redir_skip_right(proc->rd->next->str);
		else if (get_redir_type(proc->rd) == LEFT)
			ret = redir_skip_left(proc->rd->next->str);
		if (ret == -1)
			return;
		proc->rd = proc->rd->next->next;
	}
	redir_exec(proc, g_env);
}