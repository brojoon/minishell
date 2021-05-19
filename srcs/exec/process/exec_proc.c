#include "minishell.h"

void no_inst_redir(void)
{
	return ;
}

int		exec_builtin(t_inst *proc, t_env **envs)
{
	if (ft_strcmp(proc->inst, "cd") == 0)
		ft_cd(proc, *envs);
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
	int ret;
	char *path;

	ret = 0;
	path = get_path(proc->inst, *envs);
	if (proc->child != NULL)
		dup2(child->fds[1], STDOUT_FILENO);
	if (proc->fds[0] != 0)
	{
		dup2(proc->fds[0], STDIN_FILENO);
		close(proc->fds[0]);
	}
	if (exec_builtin(proc, envs))
		(ret = execve(path, inst_to_chunks(proc), envs_to_chunks(*envs)));
	if (ret == -1)
	{
		catch_error(proc->inst, "command not found");
		g_status = 2;
		exit(1);
	}
	exit(0);
}

void	exec_pipe(t_inst *proc, t_env **envs)
{
	t_inst *child;
	pid_t pid;
	int state;

	child = proc;
	if (proc->child != NULL)
	{
		child = proc->child;
		pipe(child->fds);
		if (proc->rd)
		{
			redir_init(proc, envs);
			return ;
		}
	}
	else if (proc->rd)
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
	t_inst *cur;

	cur = proc;
	while (cur != NULL)
	{
		if (cur->inst)
		{
			if (cur->child || (!(cur->rd) && exec_builtin(cur, envs)))
			{
				exec_pipe(cur, envs);
				while (cur->child)
				{
					cur = cur->child;
					exec_pipe(cur, envs);
				}
			}
			else
				redir_init(cur, envs);
		}
		else
			no_inst_redir();
		proc = proc->next;
		cur = proc;
	}
}