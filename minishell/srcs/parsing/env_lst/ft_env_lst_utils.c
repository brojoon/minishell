#include "ft_env_lst.h"

t_env	*ft_envfind(t_env *env, char *key)
{
	t_env	*curr;

	curr = env;
	if (curr == 0)
		return (0);
	while (curr && ft_strncmp(curr->key, key, ft_strlen(curr->key)) != 0)
	{
		curr = curr->next;
	}
	return (curr);
}

void	ft_envfree(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	ft_envremove(t_env **root, char *key)
{
	t_env	*curr;
	t_env	*prev;
	t_env	*del;

	curr = *root;
	prev = 0;
	while (curr)
	{
		if (ft_strncmp(curr->key, key, ft_strlen(curr->key)) == 0)
		{
			if (prev == 0)
				*root = curr->next;
			else
			{
				del = curr;
				prev->next = curr->next;
				ft_envfree(del);
			}
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	ft_envadd_back(t_env **root, t_env *now)
{
	t_env	*curr;

	if (*root == 0)
		*root = now;
	else
	{
		curr = *root;
		while (curr->next)
			curr = curr->next;
		curr->next = now;
	}
}

/*
 * flag : append 여부 (0 : remove and add, 1 : append)
*/
void	ft_envchkandadd(t_env **root, t_env *now, int flag)
{
	t_env	*curr;

	curr = ft_envfind(*root, now->key);
	if (curr == 0)
		ft_envadd_back(root, now);
	else
	{
		if (flag == 1)
			ft_resize_and_copy(&curr->value,
				now->value, 0, ft_strlen(now->value));
		else
		{
			free(curr->value);
			curr->value = ft_strdup(now->value);
		}
		ft_envfree(now);
	}
}
