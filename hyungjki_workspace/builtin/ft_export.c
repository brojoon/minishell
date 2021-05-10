#include "../minishell.h"

int get_env_size(t_env *g_env)
{
	int i;

	i = 0;
	while (g_env)
	{
		i++;
		g_env = g_env->next;
	}
	return (i);
}

void printf_export(t_env *g_env)
{
	char **envs;

	envs = env_sort(g_env);
	while(envs[])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);


	}
}

void registe_to_envs(char *arg , t_env *g_env)
{
	int i;
	t_env *new;
	
	i = -1;
	while (g_env)
		g_env = g_env->next;
	new = (t_env *)malloc(sizeof(t_env *));
	new->next = NULL;
	g_env->next = new;
	if (strchr(arg, '='))
	{
		new->key = ft_substr(arg, 0, strchr(arg, '=') - arg - 1);
		new->value = ft_substr(arg, strchr(arg, '=') - arg + 1, ft_strlen(arg) - 1);
	}
	else
		new->key = ft_strdup(arg);
}

void is_valid_export(char *key, t_env *g_env)
{
	int i;

	i = 0;
	if (!ft_isalpha(key[0]))
	{
		key = ft_strjoin("`" , key);
		key = ft_strjoin(key, "\': not a valid identifier");
		catch_error("export", key);
		return ;
	}
	while (key[++i])
	{
		if ((key[i] !='=') && (!ft_isalpha(key[i]) && !ft_isalnum(key[i])))
		{
			key = ft_strjoin("`" , key);
			key = ft_strjoin(key, "\': not a valid identifier");
			catch_error("export", key);
			return ;
		}
	}
	registe_to_envs(key, g_env);
}

void ft_export(t_inst *proc, t_env *g_env)
{
	int i;

	if (proc->arg == NULL)
		print_export(g_env);
	else
	{
		while (proc->arg)
		{
			i = -1;
			if (proc->arg->str)
				is_valid_export(proc->arg->str, g_env);
			proc->arg = proc->arg->next;
		}
	}
}