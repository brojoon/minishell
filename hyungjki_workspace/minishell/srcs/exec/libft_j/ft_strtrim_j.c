/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 04:53:40 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/03 02:47:34 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_j.h"

static int	is_set_j(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*ft_trim_allo_j(int start, int end)
{
	if (start > end)
		return ((char *)malloc(1));
	else
		return ((char *)malloc(end - start + 1 + 1));
}

static void	insert_null_j(int cur, char **result)
{
	if (cur == -1)
		(*result)[0] = '\0';
	else
		(*result)[cur] = '\0';
}

char	*ft_strtrim_j(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		cur;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (start < (int)ft_strlen_j(s1) && is_set_j(s1[start], set))
		start++;
	end = (int)ft_strlen_j(s1) - 1;
	while (end >= 0 && is_set_j(s1[end], set))
		end--;
	result = ft_trim_allo_j(start, end);
	if (result)
	{
		cur = -1;
		if (start <= end)
		{
			while (++cur <= end - start)
				result[cur] = s1[start + cur];
		}
		insert_null_j(cur, &result);
	}
	return (result);
}
