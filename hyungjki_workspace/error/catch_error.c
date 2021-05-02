#include "../minishell.h"

void	catch_error(char *msg, int errnum)
{
	char buf[1024];

	if (errnum == -1)
		errnum = errno;
	ft_putstr_fd(getcwd(buf, 1024), STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errnum), STDERR_FILENO);
	
}