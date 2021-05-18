#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int	st;

	st = 0;
	while (*(s + st))
	{
		if (*(s + st) == (char)c)
			return ((char *)(s + st));
		st++;
	}
	if (c == '\0')
		return ((char *)(s + st));
	return (0);
}

char	*ft_strrchr(char *s, int c)
{
	int		st;
	char	*ret;

	st = 0;
	ret = 0;
	while (*(s + st))
	{
		if (*(s + st) == (char)c)
			ret = (char *)(s + st);
		st++;
	}
	if (c == '\0')
		ret = (char *)(s + ft_strlen(s));
	return (ret);
}

int	ft_strncmp(char *s1, char *s2, int len)
{
	int	st;

	st = 0;
	if (s1 == 0 && s2 == 0)
		return (0);
	else if (s1 == 0 && s2 != 0)
		return (s2[0]);
	else if (s1 != 0 && s2 == 0)
		return (s1[0]);
	while (s1[st] && s2[st] && st < len)
	{
		if (s1[st] != s2[st])
			return ((unsigned char)s1[st] - (unsigned char)s2[st]);
		st++;
	}
	if (len <= 0 || st == len)
		return (0);
	return ((unsigned char)s1[st] - (unsigned char)s2[st]);
}

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	st;
	size_t	lt_len;

	st = 0;
	lt_len = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	else if (!big)
		if (big[st])
			st = 0;
	while (st + lt_len <= len)
	{
		while (big[st] && big[st] != little[0])
			st++;
		if (!big[st] || st + lt_len > len)
			break ;
		if (!ft_strncmp(&big[st], little, lt_len))
			return (&((char *)big)[st]);
		st++;
	}
	return (0);
}
