/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:51:44 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 12:51:45 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_envs_size(t_env *envs)
{
	int	size;

	size = 0;
	while (envs)
	{
		size++;
		envs = envs->next;
	}
	return (size);
}

void	swap(t_env **list, int i, int j)
{
	t_env	*tmp;

	tmp = list[i];
	list[i] = list[j];
	list[j] = tmp;
}

void	quick_sort_list(t_env **list, int first, int last)
{
	int	i;
	int	j;
	int	pivot;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;
		while (i < j)
		{
			while (ft_strcmp(list[i]->key, list[pivot]->key) <= 0 && i < last)
				i++;
			while (ft_strcmp(list[j]->key, list[pivot]->key) > 0)
				j--;
			if (i < j)
				swap(list, i, j);
		}
		swap(list, pivot, j);
		quick_sort_list(list, first, j - 1);
		quick_sort_list(list, j + 1, last);
	}
}

t_env	**quick_sort_init(t_env *envs)
{
	int		size;
	t_env	**sorted_envs;

	size = get_envs_size(envs);
	sorted_envs = (t_env **)malloc(sizeof(t_env *) * (size + 1));
	size = 0;
	while (envs)
	{
		sorted_envs[size] = envs;
		size++;
		envs = envs->next;
	}
	sorted_envs[size] = NULL;
	quick_sort_list(sorted_envs, 0, size - 1);
	return (sorted_envs);
}
