#include "../../includes/minishell.h"

int redir_skip_right(char *str)
{
	char *filename;
	int fd;

	filename = ft_strchr(str, '>') + 1;
	if (*filename == '>')
		filename++;
	while (*filename == ' ')
		filename++;
	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putendl_fd(" No such file or directory", STDERR_FILENO);
		return (-1);
	}
	close(fd);
	return (0);
}

int redir_skip_left(char *str)
{
	char *filename;
	int fd;

	filename = ft_strchr(str, '<') + 1;
	while (*filename == ' ')
		filename++;
	fd = open(filename, O_WRONLY | O_CREAT, 0744);
	close(fd);
	return (0);
}