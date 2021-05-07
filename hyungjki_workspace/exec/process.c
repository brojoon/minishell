#include "../minishell.h"

int exec_builtin(t_inst *proc)
{
	if (ft_strcmp(proc->inst, "cd") == 0)
		ft_cd(proc->arg);
	else if (ft_strcmp(proc->inst, "echo") == 0)
		ft_echo(proc->arg, proc->option);
	else if (ft_strcmp(proc->inst, "env") == 0)
		ft_env();
	else if (ft_strcmp(proc->inst, "exit") == 0)
		ft_exit(proc->arg);
	else if (ft_strcmp(proc->inst, "export") == 0)
		ft_export(proc->arg);
	else if (ft_strcmp(proc->inst, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(proc->inst, "unset") == 0)
		ft_unset(proc->arg);
	else
		return (1);
	return (0);
}

void exec_child_process(t_inst *proc, t_inst *next_proc)
{
	int ret;
	char *path;

	ret = 0;
	path = get_path(proc->inst, environ);
	if (proc->is_pipe == 1)
	{
		dup2(next_proc->fds[1], STDOUT_FILENO);
		close(next_proc->fds[1]);
	}
	if (proc->fds[0] != 0)
	{
		dup2(proc->fds[0], STDIN_FILENO);
		close(proc->fds[0]);
	}
	if (exec_builtin(proc))
		(ret = execve(path, proc->arg, environ));
	if (ret == -1)
	catch_error(proc->arg, errno);
	exit(ret);
}

void exec_pipe(t_inst *proc)
{
	t_inst *next_proc;
	pid_t pid;
	int status;

	next_proc = proc;
	if (proc->is_pipe == 1)
	{
		next_proc = proc->next;
		next_proc->is_pipe = 1;
		pipe(next_proc->fds);
	}
	pid = fork();
	if (pid == 0)
		exec_childl_process(proc, next_proc);
	waitpid(pid, &status, 0);
	if (proc->is_pipe)
		close(next_proc->fds[1]);
	if (proc->fds[0] != 0)
		close(proc->fds[0]);
}

void exec_parent_process(t_inst *proc)
{
	t_inst *cur;

	cur = proc;
	is_pipe(cur);
	while (cur != NULL)
	{
		if (cur->inst)
		{
			if (cur->is_pipe || exec_builtin(cur))
				exec_pipe(cur);
		}
		cur = cur->next;
	}
}