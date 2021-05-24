#include "minishell.h"

/*
 * (semi-colon)으로 나뉜 애들은 sibling
*/

void	ft_instadd_sibling(t_inst **root, t_inst *inst)
{
	t_inst	*curr;

	if (*root == 0)
		*root = inst;
	else
	{
		curr = *root;
		while (curr->next != 0)
			curr = curr->next;
		curr->next = inst;
	}
}

/*
** (pipe)로 나뉜 애들은 child
*/

void	ft_instadd_child(t_inst **root, t_inst *inst)
{
	t_inst	*curr;

	if (*root == 0)
		*root = inst;
	else
	{
		curr = *root;
		while (curr->child != 0)
			curr = curr->child;
		curr->child = inst;
	}
}

void	ft_inst_free(t_inst *root)
{
	t_inst	*del;

	del = root;
	while (del)
	{
		root = del->next;
		free(del->inst);
		free(del->option);
		ft_lstfree_all(del->rd);
		ft_lstfree_all(del->arg);
		ft_inst_free(del->child);
		free(del);
		del = root;
	}
}

t_inst	*ft_instinit(void)
{
	t_inst	*ret;

	ret = (t_inst *)malloc(sizeof(t_inst));
	if (ret == 0)
		return (0);
	ret->inst = 0;
	ret->option = 0;
	ret->rd = 0;
	ret->arg = 0;
	ret->next = 0;
	ret->child = 0;
	return (ret);
}

void	ft_lstfree_allrev(t_string *root)
{
	t_string	*del;

	del = root;
	while (del)
	{
		root = del->prev;
		ft_lstfree(del);
		del = root;
	}
}
