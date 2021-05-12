#include "../../includes/minishell.h"

void ft_pwd(void)
{
	char buf[1024];

	if (!(getcwd(buf, 1024)))
		catch_error("pwd", strerror(errno));
	else
		ft_putendl_fd(buf, STDOUT_FILENO);
	return ;
}