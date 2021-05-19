#include "minishell.h"

t_string	*ft_lstfind(t_string *root, char *target)
{
	t_string	*curr;

	curr = root;
	while (curr)
	{
		if (ft_strnstr(curr->str, target, ft_strlen(curr->str)) != 0)
			return (curr);
		curr = curr->next;
	}
	return (0);
}

int	ft_lstcount(t_string *arg)
{
	t_string	*curr;
	int			cnt;

	cnt = 0;
	if (arg == 0)
		return (cnt);
	else
	{
		curr = arg;
		while (curr)
		{
			curr = curr->next;
			cnt++;
		}
	}
	return (cnt);
}

void	ft_lstadd_front(t_string **root, t_string *s)
{
	t_string	*curr;

	if (*root == 0)
		*root = s;
	else
	{
		curr = s;
		while (curr->next)
			curr = curr->next;
		curr->next = *root;
		*root = s;
	}
}

void	ft_lstadd_after(t_string **root, t_string *s)
{
	if (*root == 0)
		*root = s;
	else
	{
		s->next = (*root)->next;
		(*root)->next = s;
	}
}

void	ft_lstadd_back(t_string **root, t_string *s)
{
	t_string	*curr;

	if (*root == 0)
		*root = s;
	else
	{
		curr = *root;
		while (curr->next != 0)
			curr = curr->next;
		curr->next = s;
	}
}
