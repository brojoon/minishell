#include "minishell.h"

int	ft_write_and_ret(char *inst, char *msg, int ret)
{
	write(STDERR_FILENO, "bash: ", 6);
	write(STDERR_FILENO, inst, ft_strlen(inst));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	return (ret);
}
