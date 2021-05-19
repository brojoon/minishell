#include "minishell.h"

int	proc_metachar_case_single(char **out, char *s, int *meta_arr, int *st)
{
	int	ed;

	(*st)++;
	if (s[*st] != '$' && s[*st] != '`' && s[*st] !='"' && s[*st] != '\\')
	{
		meta_arr[--(*st)] = 0;
		return (1);
	}
	if (s[*st] == '$')
	{
		ed = *st + 1;
		while (s[ed] && ((s[ed] >= 'A' && s[ed] <= 'Z')
				|| (s[ed] >= '0' && s[ed] <= '9')))
			ed++;
	}
	ed = *st;
	ft_resize_and_copy(out, s, *st, ed);
	*st = ed - 1;
	return (0);
}

int	proc_metachar_case_dollar(char **out, char *s, t_env *root, int *st)
{
	int		ed;
	t_env	*env;
	char	*num;

	ed = *st + 1;
	while (s[ed] && ((s[ed] >= 'A' && s[ed] <= 'Z')
			|| (s[ed] >= '0' && s[ed] <= '9')))
		ed++;
	env = get_env(root, ft_substr(s, *st + 1, ed));
	if (env != 0)
		ft_resize_and_copy(out, env->value, 0, ft_strlen(env->value));
	else if (s[ed] == '?')
	{
		num = ft_itoa(g_status);
		ft_resize_and_copy(out, num, 0, 1);
		free(num);
	}
	*st = ed;
	return (0);
}

int	proc_metachar_subloop(char **out, t_env *root, char *s, int *st)
{
	int		*meta_arr;
	int		ret;

	ret = 0;
	meta_arr = get_meta_arr(s);
	if (s[*st] == '\\' && meta_arr[*st] == 1 && s[*st + 1] != 0)
	{
		if (proc_metachar_case_single(out, s, meta_arr, st) == 1)
			ret = 2;
	}
	else if (s[*st] == '$' && meta_arr[*st] == 1)
		proc_metachar_case_dollar(out, s, root, st);
	else
		ft_resize_and_copy(out, &s[*st], 0, 1);
	if (s[*st] == 0)
		ret = 1;
	free(meta_arr);
	return (ret);
}

/*
 * meta char 처리 함수
*/
char	*proc_metachar(t_env *root, char *s)
{
	int		st;
	char	*ret;
	int		flag;

	st = 0;
	ret = 0;
	if (s == 0)
		return (0);
	while (s[st])
	{
		flag = proc_metachar_subloop(&ret, root, s, &st);
		if (flag == 1)
			break ;
		else if (flag == 2)
			continue ;
		st++;
	}
	return (ret);
}
