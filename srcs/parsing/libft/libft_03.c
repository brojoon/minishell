#include "main.h"

void	ft_free_chunks(char **ret, int ret_st)
{
	int	st;

	st = 0;
	if (*ret == 0)
		return ;
	while (st < ret_st)
		free(*(ret + (st++)));
	free(ret);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	ed;
	unsigned int	st;

	if (!s)
		return (0);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == 0)
		return (0);
	st = 0;
	if (ft_strlen(s) >= start)
	{
		ed = start + len;
		while (start < ed)
			ret[st++] = s[start++];
	}
	ret[st] = '\0';
	return (ret);
}

int	ft_get_next_idx(char *s, char c, int st)
{
	while (s[st] && s[st] != c)
		st++;
	return (st);
}

int	ft_cnt_lines(char *s, char c)
{
	int	st;
	int	cnt;

	st = 0;
	cnt = 0;
	while (s[st] && s[st] == c)
		st++;
	while (s[st])
	{
		st = ft_get_next_idx(s, c, st);
		cnt++;
		while (s[st] && s[st] == c)
			st++;
	}
	return (cnt);
}

char	**ft_split(char *s, char c)
{
	char	**ret;
	int		ret_st;
	int		st;

	if (!s)
		return (0);
	ret = (char **)malloc(sizeof(char *) * (ft_cnt_lines(s, c) + 1));
	ret_st = 0;
	st = 0;
	while (s[st] && s[st] == c)
		st++;
	while (s[st] && ret_st < ft_cnt_lines(s, c))
	{
		ret[ret_st++] = ft_substr(s, st, ft_get_next_idx(s, c, st) - st);
		if (ret == 0)
		{
			ft_free_chunks(ret, ret_st);
			return (0);
		}
		st = ft_get_next_idx(s, c, st);
		while (s[st] && s[st] == c)
			st++;
	}
	ret[ret_st] = 0;
	return (ret);
}
