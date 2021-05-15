#include "minishell.h"

void swap(t_env **list, int i, int j)
{
	t_env *tmp;

	tmp = list[i];
	list[i] = list[j];
	list[j] = tmp;
}

void quick_sort_list(t_env **list, int first, int last)
{
	int i;
	int j;
	int pivot;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;
		while (i  < j)
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

t_env **quick_sort_init(t_env *g_env)
{
	int size;
	t_env **sorted_g_env;

	size = get_g_env_size(g_env);
	sorted_g_env = (t_env **)malloc(sizeof(t_env *) * (size + 1));
	size = 0;
	while (g_env)
	{
		sorted_g_env[size] = g_env;
		size++;
		g_env = g_env->next;
	}
	sorted_g_env[size] = NULL;
	quick_sort_list(sorted_g_env, 0, size - 1);
	return (sorted_g_env);
}