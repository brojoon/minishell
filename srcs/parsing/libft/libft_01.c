#include "minishell.h"

int		nbr_length(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void	ft_free_chunks(char **ret, int ret_st)
{
	int	st;

	st = 0;
	if (*ret == 0)
	{
		free(ret);
		return ;
	}
	while (st < ret_st)
		free(*(ret + (st++)));
	free(ret);
}

int		ft_get_next_idx(char *s, char c, int st)
{
	while (s[st] && s[st] != c)
		st++;
	return (st);
}

int		ft_cnt_lines(char *s, char c)
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
