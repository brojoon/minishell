#include "../minishell.h"

void ft_pwd(void)
{
	char path[1024];

	if (!(getcwd(path, 1024)))
	{
		//error handle
	}
	else
		ft_putendl_fd(path, STDOUT_FILENO);
	return;
}