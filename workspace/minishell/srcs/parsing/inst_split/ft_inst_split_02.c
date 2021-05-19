#include "ft_inst_split.h"

t_inst	*split_commmads_subloop(char **pipe_chunks)
{
	int		j;
	t_inst	*root;
	t_inst	*inst;

	j = 0;
	root = 0;
	while (*(pipe_chunks + j))
	{
		inst = make_command(ft_split(*(pipe_chunks + j), ' '),
				ft_cnt_lines(*(pipe_chunks + j), ' '));
		if (inst == 0)
		{
			ft_inst_free(root);
			ft_inst_free(inst);
			return (0);
		}
		else
		{
			if (!ft_strncmp(inst->inst, "echo", ft_strlen(inst->inst)))
				echo_merge_args(&inst);
			ft_instadd_child(&root, inst);
		}
		j++;
	}
	return (root);
}

/*
 * 여러 줄으로 입력받은 명령어 문자열을 |, ; 단위로 split 후 make_command 함수 호출
 * ;(semi colon)은 inst->next, |(pipe)는 inst->child로 attach
*/
t_inst	*split_commands(char **semi_chunks, int line_cnt)
{
	int		i;
	char	**pipe_chunks;
	t_inst	*root;
	t_inst	*temp_root;
	int		chunk_size;

	root = 0;
	if (semi_chunks == 0)
		return (0);
	i = 0;
	while (*(semi_chunks + i))
	{
		pipe_chunks = ft_split(*(semi_chunks + i), '|');
		chunk_size = ft_cnt_lines(*(semi_chunks + i), '|');
		temp_root = split_commmads_subloop(pipe_chunks);
		ft_free_chunks(pipe_chunks, chunk_size);
		if (temp_root != 0)
			ft_instadd_sibling(&root, temp_root);
		i++;
	}
	ft_free_chunks(semi_chunks, line_cnt);
	return (root);
}

/*
 * execve에 넣기 위한 t_string *의 형식 변경 함수
*/
char	**inst_to_chunks(t_inst *inst)
{
	char		**ret;
	t_string	*curr;
	int			st;

	ret = (char **)malloc(sizeof(char *) * (ft_lstcount(inst->arg) + 3));
	if (ret == 0)
		return (0);
	st = 0;
	*(ret + st++) = inst->inst;
	if (inst->option)
		*(ret + st++) = inst->option;
	curr = inst->arg;
	while (curr)
	{
		*(ret + (st++)) = curr->str;
		curr = curr->next;
	}
	*(ret + st) = 0;
	return (ret);
}
