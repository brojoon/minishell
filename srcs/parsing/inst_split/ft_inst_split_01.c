#include "main.h"

int	handle_red_case_01(char **chunks, char *red, t_inst *inst, char *now)
{
	if (is_fd(chunks[0]) == 0)
	{
		if (chunks[0][0] == '2' && red[0] == '>')
			chunks[0][0] = '0';
		else if (!(chunks[0][0] == '1' && red[0] == '>')
			&& !(chunks[0][0] == '0' && red[0] == '<'))
			ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(chunks[0])));
	}
	else if (is_fd(chunks[0]) == 1)
	{
		if (inst->inst == 0)
			inst->inst = ft_strdup(chunks[0]);
		else
			ft_lstadd_back(&(inst->arg), ft_lstinit(ft_strdup(chunks[0])));
	}
	else
	{
		ft_write_and_ret(chunks[0], "invalid file descriptor", 1);
		ft_free_chunks(chunks, ft_cnt_lines(now, red[0]));
		return (1);
	}
	ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(red)));
	ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(chunks[1])));
	return (0);
}

int	handle_red_case_02(char **cmd, char *red, t_inst *inst, int *k)
{
	char	**chunks;
	char	*now;

	now = *(cmd + *k);
	chunks = split_redirection(now, &red);
	ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(chunks[0])));
	if (ft_strncmp(now, red, ft_strlen(red)) == 0)
		ft_lstadd_front(&(inst->rd), ft_lstinit(ft_strdup(red)));
	else
	{
		ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(red)));
		if (*(cmd + *k + 1) == 0)
		{
			ft_free_chunks(chunks, ft_cnt_lines(now, red[0]));
			return (3);
		}
		ft_lstadd_back(&(inst->rd),
			ft_lstinit(ft_strdup(*(cmd + ++(*k)))));
	}
	ft_free_chunks(chunks, ft_cnt_lines(now, red[0]));
	return (0);
}

int	handle_red_case_03(char **cmd, char *red, t_inst *inst, int *k)
{
	char	**chunks;
	char	*now;

	now = *(cmd + *k);
	chunks = split_redirection(now, &red);
	if (*(cmd + *k + 1) == 0)
	{
		ft_free_chunks(chunks, ft_cnt_lines(*(cmd + *k), red[0]));
		return (3);
	}
	ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(red)));
	ft_lstadd_back(&(inst->rd), ft_lstinit(ft_strdup(*(cmd + ++(*k)))));
	return (0);
}

/*
 * space 단위로 쪼개진 chunk에서 '<', '>', '>>' catch
 * redirection으로 쪼갰을 때 2개가 나오면 왼쪽은 fd 혹은 명령어/인자
 * ret 0 : 정상
 * ret 1 : fd가 잘못된 경우
 * ret 2 : redirection 오류
 * ret 3 : parse error
*/
int	handle_red_token(t_inst *inst, char **cmd, int *k)
{
	char	*red;
	char	**chunks;

	red = 0;
	if (check_red_error(*(cmd + *k)) != 0)
		return (ft_write_and_ret(*(cmd + *k), "invalid redirection", 2));
	chunks = split_redirection(*(cmd + *k), &red);
	if (red == 0)
		return (-1);
	if (ft_cnt_lines(*(cmd + *k), red[0]) == 2)
	{
		if (handle_red_case_01(chunks, red, inst, *(cmd + *k)) == 1)
			return (1);
	}
	else if (ft_cnt_lines(*(cmd + *k), red[0]) == 1)
	{
		if (handle_red_case_02(cmd, red, inst, k) == 3)
			return (ft_write_and_ret(*(cmd + *k), "parse error", 3));
	}
	else
		if (handle_red_case_03(cmd, red, inst, k) == 3)
			return (ft_write_and_ret(*(cmd + *k), "parse error", 3));
	ft_free_chunks(chunks, ft_cnt_lines(*(cmd + *k), red[0]));
	return (0);
}
