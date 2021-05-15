#include "../../includes/minishell.h"

void del_env(char *key, t_env *g_env)
{
	t_env *tmp;
	t_env *cur;

	cur = g_env;
	printf("2\n");
	while (cur)
	{
		if (ft_strcmp(cur->key, key))
		{
			tmp = cur->next;
			while (g_env->next != cur)
				g_env = g_env->next;
			g_env->next = tmp;
			free(cur->key);
			free(cur->value);
			free(cur);
			cur = NULL;
			break;
		}
		cur = cur->next;
	}
}

int check_valid_env_key(char *key)
{
	if (!key)
		return (0);
	if (ft_isdigit(*key))
		return (0);
	while(*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

void ft_unset(t_inst *proc, t_env *g_env)
{
	char *err_msg;
	t_string *arg;
	printf("-1\n");
	arg = proc->arg;
	if (!g_env || !arg)
		return ;
	printf("0\n");
	while (arg)
	{
		printf("1\n");
		if (!check_valid_env_key(arg->str))
		{
			err_msg = ft_strjoin("`" ,arg->str);
			err_msg = ft_strjoin(err_msg, "\': not a valid identifier");			
			catch_error(proc->inst, err_msg);
			free(err_msg);
			break;
		}
		else
			del_env(arg->str, g_env);
		arg = arg->next;
	}
}