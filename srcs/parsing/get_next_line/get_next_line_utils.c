#include "minishell.h"

int	ft_memset(char **line, size_t size)
{
	size_t	st;

	*line = (char *)malloc(sizeof(char) * (size + 1));
	if (*line == 0)
		return (-1);
	st = 0;
	while (st < size)
		*(*line + st++) = '\0';
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	st;

	st = 0;
	while (src[st] && st + 1 < dstsize)
	{
		dst[st] = src[st];
		st++;
	}
	if (dstsize > 0)
		dst[st] = '\0';
	return (0);
}

void	ft_resize_and_copy(char **line, char *buf, int st, int ed)
{
	char	*temp;
	int		mem_size;
	int		line_len;

	line_len = ft_strlen(*line);
	mem_size = line_len + ed - st + 1;
	ft_memset(&temp, mem_size);
	if (*line)
	{
		ft_strlcpy(temp, *line, line_len + 1);
		free(*line);
		*line = 0;
	}
	ft_strlcpy(temp + line_len, buf + st, ed - st + 1);
	*line = temp;
}

int	recover_term(t_cursor *cursor)
{
	ft_lstfree_allrev(cursor->history);
	cursor->term.c_lflag |= ICANON;
	cursor->term.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &(cursor->term));
	ft_putstr_fd("\b\b \b\b\n", STDIN_FILENO);
	return (-1);
}

/*
 * buf의 st ~ ed를 char *to로 치환하는 함수
*/
char	*replace_str(char **buf, int st, int ed, char *to)
{
	char	*temp;
	char	*now_str;

	temp = 0;
	if (st == ed - 1)
		return (0);
	now_str = ft_substr(*buf, st, ed - st + 1);
	ft_resize_and_copy(&temp, *buf, 0, st);
	ft_resize_and_copy(&temp, to, 0, ft_strlen(to));
	ft_resize_and_copy(&temp, *buf, ed + 1, ft_strlen(*buf));
	free(*buf);
	*buf = temp;
	return (now_str);
}
