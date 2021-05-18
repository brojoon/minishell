/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 04:54:44 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/01 06:40:01 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_j.h"

static int	len_th_j(long long n)
{
	long long	result;

	result = 0;
	if (n <= 0)
		result = 1;
	if (n < 0)
		n *= -1;
	while (n)
	{
		n /= 10;
		result++;
	}
	return (result);
}

void	set_numbers_j(char **result, long long *numbers, long long n)
{
	if (n <= 0)
	{
		if (n == 0)
			(*result)[0] = '0';
		else
			(*result)[0] = '-';
	}
	if (n < 0)
		*numbers = -n;
	if (n >= 0)
		*numbers = n;
}

char	*ft_itoa_j(int n)
{
	char		*result;
	long long	numbers;
	long long	len;

	result = (char *)malloc(len_th_j(n) + 1);
	if (result)
	{
		len = len_th_j(n);
		result[len--] = '\0';
		set_numbers_j(&result, &numbers, n);
		while (numbers)
		{
			result[len--] = numbers % 10 + '0';
			numbers /= 10;
		}
	}
	return (result);
}
