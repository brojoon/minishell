#include "minishell.h"

void	ft_pwd(void)
{
	char	buf[1024];

	if (!(getcwd(buf, 1024)))
	{
		catch_error("pwd", strerror(errno));
		g_status = 1;
	}
	else
	{
		ft_putendl_fd_j(buf, STDOUT_FILENO);
		g_status = 0;
	}
	return ;
}
