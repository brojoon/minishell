#include "../minishell.h"

t_env *get_env(t_env *env, char *key)
{
	while (env)
	{
		if (env->key)
			if (ft_strcmp(env->key, key) == 0)
				return (env);
		env = env->next;
	}
}

void edit_env_value(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (env->key)
			if (ft_strcmp(env->key, key) == 0)
			{
				free(env->value);
				env->value = value;
				break;
			}	
		env = env->next;
	}
}

void ft_env(char **environ)
{
	t_env *node;

	node = g_env;
	while (node)
	{
		if ((node->key) || (node->value))
		{
			ft_putstr_fd(node->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(node->value, STDOUT_FILENO);
		}
		node = node->next;
	}
	return ;
}