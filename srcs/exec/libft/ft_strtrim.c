/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 04:53:40 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 13:34:13 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*ft_trim_allo(int start, int end)
{
	if (start > end)
		return ((char *)malloc(1));
	else
		return ((char *)malloc(end - start + 1 + 1));
}

static void	insert_null(int cur, char **result)
{
	if (cur == -1)
		(*result)[0] = '\0';
	else
		(*result)[cur] = '\0';
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		cur;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (start < (int)ft_strlen(s1) && is_set(s1[start], set))
		start++;
	end = (int)ft_strlen(s1) - 1;
	while (end >= 0 && is_set(s1[end], set))
		end--;
	result = ft_trim_allo(start, end);
	if (result)
	{
		cur = -1;
		if (start <= end)
		{
			while (++cur <= end - start)
				result[cur] = s1[start + cur];
		}
		insert_null(cur, &result);
	}
	return (result);
}
