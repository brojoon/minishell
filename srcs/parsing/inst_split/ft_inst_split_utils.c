#include "minishell.h"

void	get_splitter(char *str, char **splitter)
{
	if (splitter == 0)
		*splitter = 0;
	if (ft_strchr(str, '>') != 0)
	{
		if (ft_strnstr(str, ">>", ft_strlen(str)) != 0)
			*splitter = ">>";
		else
			*splitter = ">";
	}
	else if (ft_strchr(str, '<') != 0)
		*splitter = "<";
}

/*
 * 명령어 및 인자에 redireciton이 있는지 확인
 * redirection은 splitter에 넣어주고 splitter로 자른 char **를 return
*/
char	**split_redirection(char *str, char **splitter)
{
	char	**ret;

	get_splitter(str, splitter);
	ret = 0;
	if (splitter)
		ret = ft_split(str, (*splitter)[0]);
	return (ret);
}

/*
 * 한번에 2개 이상의 redirection이 붙어있는 경우 error
*/
int	check_red_error(char *inst)
{
	int	num_of_lines;
	int	num_of_lines2;

	num_of_lines = ft_cnt_lines(inst, '>');
	num_of_lines2 = ft_cnt_lines(inst, '<');
	if (num_of_lines > 2 || num_of_lines2 > 2)
		return (1);
	if (ft_strchr(inst, '<') && ft_strchr(inst, '>'))
		return (1);
	return (0);
}

/*
 * ret 0 : 정상 fd (0 ~ 2)
 * ret 1 : not fd (inst or argument)
 * ret 2 : 3 ~ 9 사이의 fd
*/
int	is_fd(char *s)
{
	size_t	st;

	st = 0;
	if (ft_strlen(s) > 1)
	{
		while (s[st] && s[st] >= '0' && s[st] <= '9')
			st++;
		if (st == ft_strlen(s))
			return (2);
		else
			return (1);
	}
	if (*s < '0' || *s > '9')
		return (1);
	else if (*s > '2' && *s <= '9')
		return (2);
	return (0);
}

/*
 * echo인 경우 arg를 모두 합침
 * arg + ' ' + arg 형식
*/
void	echo_merge_args(t_inst **inst)
{
	t_string	*arg;
	char		*temp;

	temp = 0;
	arg = (*inst)->arg;
	if (arg == 0)
		return ;
	while (arg)
	{
		ft_resize_and_copy(&temp, arg->str, 0, ft_strlen(arg->str));
		if (arg->next)
			ft_resize_and_copy(&temp, " ", 0, 1);
		arg = arg->next;
	}
	ft_lstfree_all((*inst)->arg);
	(*inst)->arg = ft_lstinit(temp);
}
