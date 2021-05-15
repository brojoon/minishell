#include "get_next_line.h"

int		ft_memset1(char **line, size_t size)
{
	size_t	st;

	if (!(*line = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	st = 0;
	while (st < size)
		*(*line + st++) = '\0';
	return (0);
}

int		ft_get_next_idx(char *s, char c, int st)
{
	while (s[st] && s[st] != c)
		st++;
	return (st);
}

size_t	ft_strlcpy1(char *dst, const char *src, size_t dstsize)
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

	line_len = ft_strlen1(*line);
	mem_size = line_len + ed - st + 1;
	ft_memset1(&temp, mem_size);
	if (*line)
	{
		ft_strlcpy1(temp, *line, line_len + 1);
		free(*line);
		*line = 0;
	}
	ft_strlcpy1(temp + line_len, buf + st, ed - st + 1);
	*line = temp;
}

char	*ft_strdup1(char *str)
{
	char	*ret;
	int		st;

	if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen1(str) + 1))))
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
