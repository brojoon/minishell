#include "../minishell.h"

void ft_unset(t_string *arg)
{
	g_env **env_list;
	g_env *node_list;

	env_list = get_env_list();
	node_list = *env_list;
	if (env_list || arg)
		return ;
	while (arg)
	{
		
		arg = arg->next;
	}
}