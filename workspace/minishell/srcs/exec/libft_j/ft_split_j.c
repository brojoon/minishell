/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 04:54:26 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/03 06:34:07 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_j.h"

static size_t	strslen_j(const char *s, char c)
{
	size_t		result;

	result = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s != c && *s != '\0')
				s++;
			result++;
		}
		else
			s++;
	}
	return (result);
}

static size_t	free_strs_j(char **result, size_t cur)
{
	int		idx;

	idx = -1;
	while (++idx < (int)cur)
	{
		free(result[idx]);
		result[idx] = NULL;
	}
	return (1);
}

static size_t	init_split_j(char **result, const char *s, char c, size_t len)
{
	size_t	cur;
	size_t	count;
	size_t	i;

	cur = 0;
	i = 0;
	while (s[i] && cur < len)
	{
		count = 0;
		if (s[i] != c)
		{
			while (s[i + count] != c && s[i + count] != '\0')
				count++;
			result[cur] = ft_substr_j(s, i, count);
			if (!result[cur])
				return (free_strs_j(result, cur));
			cur++;
			i += count - 1;
		}
		i++;
	}
	return (0);
}

char	**ft_split_j(char const *s, char c)
{
	char	**result;
	size_t	len;

	if (!s)
		return (NULL);
	len = strslen_j(s, c);
	result = (char **)malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	if (init_split_j(result, s, c, len))
	{
		free(result);
		result = NULL;
		return (result);
	}
	result[len] = NULL;
	return (result);
}
