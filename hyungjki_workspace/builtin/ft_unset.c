#include "../minishell.h"

void del_env(char *key)
{
	t_env *list;
	t_env *tmp;

	list = g_env;

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
}

void ft_unset(t_string *arg)
{
	char *err_msg;

	if (g_env || arg)
		return ;
	while (arg)
	{
		if (!check_valid_env_key(arg->str))
		{
			err_msg = ft_strjoin("\'" ,arg->str);			
			error_msg_join("unset: `", arg->str);
			free(err_msg);
			break;
		}
		else
			del_env(arg->str);
		arg = arg->next;
	}
}