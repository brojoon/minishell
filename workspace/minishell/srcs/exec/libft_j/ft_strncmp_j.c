/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 10:39:55 by hyungjki          #+#    #+#             */
/*   Updated: 2020/12/31 05:57:03 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_j.h"

int	ft_strncmp_j(const char *s1, const char *s2, size_t size)
{
	size_t	n;

	n = 0;
	while (n < size && s1[n] && s2[n])
	{
		if (s1[n] != s2[n])
			break ;
		n++;
	}
	if (n == size)
		return (0);
	return ((unsigned char)s1[n] - (unsigned char)s2[n]);
}
