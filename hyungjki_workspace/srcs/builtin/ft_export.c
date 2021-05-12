#include "../../includes/minishell.h"

void print_export(t_env *g_env)
{
	return ;
}

int is_valid_export(char *str, t_env *g_env)
{
	int i;

	i = -1;
	if (!(ft_isalpha(str[0])) && !(str[0] == '_'))
		return (1);
	while (str[i++])
	{
		if (!(ft_isalpha(str[i])) && !(str[i] == '_') && \
			!(ft_isdigit(str[i])))
			return (1);
	}
	while (g_env)
	{
		while (g_env[i])
		g_env = g_env->next;
	}
	return (0);
}

void ft_export(t_inst *proc, t_env *g_env)
{
	if (proc->arg == NULL)
		print_export(g_env);
	else
	{
		while (proc->arg)
		{
			if (is_valid_export(proc->arg->str, g_env))
				return ;
			add_export(proc->arg->str, g_env);
			proc->arg = proc->arg->next;
		}
	}
}