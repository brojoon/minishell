#include "minishell.h"

int redir_skip_left(char *str)
{
	char *filename;
	int fd;

	filename = str;
	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_putstr_fd_j("bash: ", STDERR_FILENO);
		ft_putstr_fd_j(filename, STDERR_FILENO);
		ft_putendl_fd_j(" No such file or directory", STDERR_FILENO);
		return (-1);
	}
	close(fd);
	return (0);
}

int redir_skip_right(char *str)
{
	char *filename;
	int fd;

	filename = str;
	fd = open(filename, O_WRONLY | O_CREAT, 0744);
	close(fd);
	return (0);
}