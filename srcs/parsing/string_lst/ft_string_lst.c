#include "minishell.h"

t_string	*ft_lstinit(char *s)
{
	t_string	*temp;

	temp = (t_string *)malloc(sizeof(t_string));
	if (temp == 0)
		return (0);
	temp->str = s;
	temp->next = 0;
	return (temp);
}

void	ft_lstfree(t_string *del)
{
	free(del->str);
	free(del);
	del = 0;
}

t_string	*ft_lstremove(t_string **root, t_string *target)
{
	t_string	*curr;
	t_string	*prev;
	t_string	*del;

	del = target;
	curr = *root;
	prev = 0;
	while (curr && ft_strncmp(curr->str, target->str,
			ft_strlen(curr->str)) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev == 0)
		*root = curr->next;
	else
		prev->next = curr->next;
	ft_lstfree(del);
	if (prev == 0)
		return (*root);
	return (prev->next);
}

void	ft_lstfree_all(t_string *root)
{
	t_string	*del;

	del = root;
	while (del)
	{
		root = del->next;
		ft_lstfree(del);
		del = root;
	}
}

int	ft_lst_get_len(t_string *root)
{
	t_string	*curr;
	int			cnt;

	curr = root->next;
	cnt = 0;
	while (curr)
	{
		cnt++;
		curr = curr->next;
	}
	return (cnt);
}
