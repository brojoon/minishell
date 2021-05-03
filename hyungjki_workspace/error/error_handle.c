#include "../minishell.h"

void error_msg_join(char *arg1, char *arg2)
{
	char *joined;
	
	joined = ft_strjoin(arg1, arg2);
	if (!joined)
		exit(1);
	catch_error(joined, errno);
	free(joined);
}

void	catch_error(char *msg, int errnum)
{
	char buf[1024];

	if (errnum == -1)
		errnum = errno;
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errnum), STDERR_FILENO);
}

