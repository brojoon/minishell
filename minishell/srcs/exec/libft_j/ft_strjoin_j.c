/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 04:52:56 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/06 03:05:19 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_j.h"

char	*ft_strjoin_j(char const *s1, char const *s2)
{
	char	*result;
	int		cur;

	cur = 0;
	result = (char *)malloc(ft_strlen_j(s1) + ft_strlen_j(s2) + 1);
	if (result)
	{
		while (*s1)
		{
			result[cur++] = *s1;
			s1++;
		}
		while (*s2)
		{
			result[cur++] = *s2;
			s2++;
		}
		result[cur] = '\0';
	}
	return (result);
}
