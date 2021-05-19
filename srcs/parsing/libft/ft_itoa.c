#include "main.h"

char	*ft_rev_str(char *n, int size)
{
	char	*ret;
	int		st;
	int		ret_st;

	st = size - 1;
	ret_st = 0;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (ret == 0)
		return (0);
	while (st >= 0)
		ret[ret_st++] = n[st--];
	ret[ret_st] = '\0';
	return (ret);
}

char	*ft_conv_int_to_char(unsigned int n, int sign)
{
	int					st;
	char				n_char[11];
	unsigned int		div;

	st = 0;
	div = n;
	while (div)
	{
		n_char[st++] = n % DIVISOR + '0';
		n = div;
		div = n / DIVISOR;
	}
	n_char[st++] = n + '0';
	if (sign == -1)
		n_char[st++] = '-';
	return (ft_rev_str(n_char, st));
}

char	*ft_itoa(int n)
{
	int	sign;

	if (n < 0)
		sign = -1;
	else
		sign = 1;
	return (ft_conv_int_to_char((unsigned int)(n * sign), sign));
}
