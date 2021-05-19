#include "minishell.h"

void	error_msg_join(char *arg1, char *arg2, char *arg3)
{
	char	*joined;

	joined = ft_strjoin_j(arg1, arg2);
	if (!joined)
		exit(1);
	catch_error(joined, arg3);
	free(joined);
}

void	catch_error(char *inst, char *msg)
{
	ft_putstr_fd_j("bash: ", STDERR_FILENO);
	ft_putstr_fd_j(inst, STDERR_FILENO);
	ft_putstr_fd_j(": ", STDERR_FILENO);
	ft_putendl_fd_j(msg, STDERR_FILENO);
}
