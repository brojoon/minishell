#include "../../includes/minishell.h"

void del_env(char *key, t_env **g_env)
{
	t_env *list;
	t_env *tmp;

	list = *g_env;

	while (list->next)
	{
		if (*(list->next->key) == *key)
		{
			tmp = list->next->next;
			free(list->next->key);
			free(list->next->value);
			free(list->next);
			list->next = tmp;
			break;
		}
		list = list->next;
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

void ft_unset(t_inst *proc, t_env **g_env)
{
	char *err_msg;
	t_string *arg;

	arg = proc->arg;
	if (*g_env || arg)
		return ;
	while (arg)
	{
		if (!check_valid_env_key(arg->str))
		{
			err_msg = ft_strjoin("\'" ,arg->str);			
			error_msg_join("unset: `", arg->str, errno);
			free(err_msg);
			break;
		}
		else
			del_env(arg->str, g_env);
		arg = arg->next;
	}
}