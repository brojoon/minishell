/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 10:42:16 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/03 06:23:27 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_j.h"

char	*ft_strnstr_j(const char *big, const char *little, size_t size)
{
	size_t	len;

	if (*little == '\0')
		return ((char *)big);
	len = ft_strlen_j(little);
	while (*big && (size-- >= len))
	{
		if (*big == *little && ft_strncmp_j(big, little, len) == 0)
			return ((char *)big);
		big++;
	}
	return (0);
}
