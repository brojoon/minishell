#include "main.h"

size_t	ft_strlen(const char *str)
{
	size_t	st;

	if (!str || !*str)
		return (0);
	st = 0;
	while (str[st])
		st++;
	return (st);
}

int	nbr_length(int n)
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

int	ft_make_int(const char *ptr, int st, int ed, int sign)
{
	unsigned long	ret;
	unsigned long	mod;

	ret = 0;
	mod = 1;
	while (--ed >= st)
	{
		ret += (((unsigned long)(ptr[ed] - '0')) * mod);
		mod *= 10;
	}
	if (ret > 2147483647 && sign == 1)
		return (-1);
	else if (ret > 2147483648 && sign == -1)
		return (0);
	return (ret * sign);
}

int	ft_atoi(const char *nptr)
{
	int		st;
	int		ed;
	int		sign;

	sign = 1;
	st = 0;
	while (nptr[st] && (nptr[st] == ' '
			|| (nptr[st] >= 0x09 && nptr[st] <= 0x0D)))
		st++;
	if (!nptr[st])
		return (0);
	if (nptr[st] == '-')
		sign = -1;
	if (sign == -1 || nptr[st] == '+')
		st++;
	if (nptr[st] < '0' || nptr[st] > '9')
		return (0);
	ed = st;
	while (nptr[ed] >= '0' && nptr[ed] <= '9')
		ed++;
	return (ft_make_int(nptr, st, ed, sign));
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}
