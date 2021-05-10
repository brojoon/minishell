#include "../minishell.h"

void error_msg_join(char *arg1, char *arg2, int errnum)
{
	char *joined;
	
	joined = ft_strjoin(arg1, arg2);
	if (!joined)
		exit(1);
	catch_error(joined, strerror(errnum));
	free(joined);
}

void	catch_error(char *inst, char *msg)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(inst, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

