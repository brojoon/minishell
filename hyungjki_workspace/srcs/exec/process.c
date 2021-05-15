#include "minishell.h"

int exec_builtin(t_inst *proc, t_env *g_env)
{
	if (ft_strcmp(proc->inst, "cd") == 0)
		ft_cd(proc, g_env);
	else if (ft_strcmp(proc->inst, "echo") == 0)
		ft_echo(proc, proc->option);
	else if (ft_strcmp(proc->inst, "env") == 0)
		ft_env(g_env);
	else if (ft_strcmp(proc->inst, "exit") == 0)
		ft_exit(proc);
	else if (ft_strcmp(proc->inst, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(proc->inst, "unset") == 0)
		ft_unset(proc, g_env);
	else if (ft_strcmp(proc->inst, "export") == 0)
		ft_export(proc, g_env);
	else
		return (1);
	return (0);
}

void exec_child_process(t_inst *proc, t_inst *child, t_env *g_env)
{
	int ret;
	char *path;
	char **argv;
	char **envs;
	envs = envs_to_chunks(g_env);
	argv = inst_to_chunks(proc);
	ret = 0;
	path = get_path(proc->inst, g_env);
	printf("proc: %s\n", proc->inst);
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
	if (exec_builtin(proc, g_env))
		(ret = execve(path, argv, envs));
	if (ret == -1)
		catch_error(proc->inst, "command not found");
	exit(ret);
}

void exec_pipe(t_inst *proc, t_env *g_env)
{
	t_inst *child;
	pid_t pid;
	int status;

	child = proc;
	if (proc->child != NULL)
	{
		child = proc->child;
		pipe(child->fds);
	}
	pid = fork();
	if (pid == 0)
		exec_child_process(proc, child, g_env);
	waitpid(pid, &status, 0);
	if (proc->child)
		close(child->fds[1]);
	if (proc->fds[0] != 0)
		close(proc->fds[0]);
}

void exec_parent_process(t_inst *proc, t_env *g_env)
{
	t_inst *cur;
	t_inst *tmp;

	cur = proc;
	tmp = proc;
	while (cur != NULL)
	{
		if (cur->inst)
		{
			if (cur->rd)
			{
				printf("3\n");
				redir_init(cur, g_env);
			}
			else if (cur->child || exec_builtin(cur, g_env))
			{
				exec_pipe(cur, g_env);
				while (cur->child)
				{
					cur = cur->child;
					exec_pipe(cur, g_env);
				}
			}
		}
		tmp = tmp->next;
		cur = tmp;
	}
}