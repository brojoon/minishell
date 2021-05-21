#include "minishell.h"

void	proc_consts(t_env *root, t_string **consts)
{
	t_string	*now;

	now = *consts;
	while (now)
	{
		proc_quotes(root, &(now->str));
		now = now->next;
	}
}

int	get_ori_consts_subloop(char **arg, t_string **const_now)
{
	int			st;
	char		*temp;
	char		*encap_str;

	st = 0;
	temp = 0;
	while ((*arg)[st])
	{
		encap_str = encap_quotes("%%", (*arg)[st]);
		if (((*arg)[st] == '\'' || (*arg)[st] == '\"')
				&& (ft_strncmp(*arg + st, encap_str, 4) == 0))
		{
			ft_resize_and_copy(&temp, (*const_now)->str,
				0, ft_strlen((*const_now)->str));
			st += 3;
			*const_now = (*const_now)->next;
		}
		else
			ft_resize_and_copy(&temp, *arg, st, st + 1);
		free(encap_str);
		st++;
	}
	free(*arg);
	*arg = temp;
	return (0);
}

/*
 * const_strings에 묶인 문자열을 inst에 있는 문자열 %%와 치환
*/
void	get_ori_consts(t_string *str, t_inst **inst_now)
{
	t_inst		*curr;
	t_string	*arg;
	t_string	*const_now;

	curr = *inst_now;
	const_now = str;
	while (curr)
	{
		if (curr->inst)
			get_ori_consts_subloop(&(curr->inst), &const_now);
		arg = curr->arg;
		while (arg)
		{
			get_ori_consts_subloop(&(arg->str), &const_now);
			arg = arg->next;
		}
		curr = curr->child;
	}
}

void	proc_inst_metachar_subloop(t_env *root, t_inst *children)
{
	char		*new_str;
	t_string	*arg;

	new_str = proc_metachar(root, children->inst);
	free(children->inst);
	children->inst = new_str;
	arg = children->arg;
	while (arg != 0)
	{
		new_str = proc_metachar(root, arg->str);
		free(arg->str);
		arg->str = new_str;
		arg = arg->next;
	}
}

void	proc_inst_metachar(t_env *root, t_inst **insts)
{
	t_inst		*now;
	t_inst		*children;

	now = *insts;
	while (now)
	{
		children = now;
		while (children)
		{
			proc_inst_metachar_subloop(root, children);
			children = children->child;
		}
		now = now->next;
	}
}
