#include "ft_inst_split.h"

/*
 * '-'로 시작하는 경우 option과 arg가 모두 비어있으면 option,
 * arg가 이미 나온 경우에는 arg에 붙여줌
*/
void	make_command_case_op(t_inst *inst, char *str)
{
	t_string	*arg;

	if (inst->arg == 0 && inst->option == 0)
		inst->option = ft_strdup(str);
	else if (inst->arg != 0)
	{
		arg = ft_lstinit(ft_strdup(str));
		ft_lstadd_back(&inst->arg, arg);
	}
}

/*
 * ["", ''] 같은 빈 문자열은 날려줌
*/
void	make_command_case_arg(t_inst *inst, char *str)
{
	t_string	*arg;

	arg = ft_lstinit(ft_strdup(str));
	if (ft_strncmp(arg->str, "\"\"", ft_strlen(arg->str)) == 0)
		ft_lstfree(arg);
	else if (ft_strncmp(arg->str, "\'\'", ft_strlen(arg->str)) == 0)
		ft_lstfree(arg);
	else
		ft_lstadd_back(&inst->arg, arg);
}

int	make_command_case_01(t_inst *new_inst, char **space_chunks, int k)
{
	if (new_inst->inst == 0)
		new_inst->inst = ft_strdup(*(space_chunks + k));
	else if (ft_strncmp(*(space_chunks + k), "-", 1) == 0)
		make_command_case_op(new_inst, *(space_chunks + k));
	else
		make_command_case_arg(new_inst, *(space_chunks + k));
	return (0);
}

/*
 * redirection은 어느 위치든 나올 수 있음
 * -로 시작하면 option으로 인식(인자 뒤에 나올 경우 인자로 인식)
 * -로 시작하는 option이 여러개인 경우 첫 번째만 인식
*/
t_inst	*make_command(char **space_chunks, int line_cnt)
{
	int			k;
	t_inst		*ret;
	int			flag;

	ret = ft_instinit();
	k = 0;
	while (*(space_chunks + k))
	{
		flag = handle_red_token(ret, space_chunks, &k);
		if (flag > 0)
		{
			printf("make_commmand err:%d\n", flag);
			ft_inst_free(ret);
			return (0);
		}
		else if (flag == -1)
			make_command_case_01(ret, space_chunks, k);
		k++;
	}
	ft_free_chunks(space_chunks, line_cnt);
	return (ret);
}
