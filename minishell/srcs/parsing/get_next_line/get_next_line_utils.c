#include "get_next_line.h"

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

void	recover_term(t_cursor *cursor)
{
	tcgetattr(STDIN_FILENO, &(cursor->term));
	cursor->term.c_lflag &= ICANON;
	cursor->term.c_lflag &= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &(cursor->term));
}

char	*ft_strdup(char *str)
{
	char	*ret;
	int		st;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (ret == 0)
		return (0);
	st = 0;
	while (str[st])
	{
		ret[st] = str[st];
		st++;
	}
	ret[st] = '\0';
	return (ret);
}
