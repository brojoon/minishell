#include "../minishell.h"

void ft_cd(t_string *arg)
{
	char *perr;
	if (arg == NULL || arg->str == NULL)
		return ;
	if (chdir(arg->str) == -1)
	{
		//error handle
	}
	//alter_pwd(g_env);
	return ;
}