#include "minishell.h"
int	quotes_sub_loop(char **buf, int **meta_arr, char target, t_cursor *cursor)
{
	char	*temp;

	while (cnt_quotes(*buf, target, *meta_arr) % 2 == 1)
	{
		get_next_line(0, &temp, "> ", cursor);
		ft_resize_and_copy(buf, "\n", 0, 1);
		ft_resize_and_copy(buf, temp, 0, ft_strlen(temp));
		free(temp);
		free(*meta_arr);
		*meta_arr = get_meta_arr(*buf);
	}
	return (0);
}

void	handle_quotes_subcase(char **buf,
			t_string **const_strings, int **meta_arr, int *st)
{
	int		ed;
	char	*rep;
	char	now;
	char	*prev_str;

	now = *(*buf + *st);
	rep = encap_quotes("%%", now);
	ed = ft_get_next_idx(*buf, now, *st + 1);
	while ((*meta_arr)[ed] == 0)
		ed = ft_get_next_idx(*buf, now, ed + 1);
	prev_str = replace_str(buf, *st, ed, rep);
	if (prev_str != 0)
	{
		ft_lstadd_back(const_strings, ft_lstinit(prev_str));
		free(*meta_arr);
		*meta_arr = get_meta_arr(*buf);
	}
	free(rep);
	*st = ft_get_next_idx(*buf, now, *st + 1);
}

/*
 * quotes(", ')사이의 string을 const_strings로 옮기고 %%로 변경
*/
void	handle_quotes(char **buf, t_string **const_strings, t_cursor *cursor)
{
	int		st;
	char	now;
	int		*meta_arr;

	meta_arr = get_meta_arr(*buf);
	st = 0;
	now = *(*buf + st);
	while (now)
	{
		if ((now == '\'' || now == '\"') && meta_arr[st] == 1)
		{
			quotes_sub_loop(buf, &meta_arr, now, cursor);
			handle_quotes_subcase(buf, const_strings, &meta_arr, &st);
		}
		now = *(*buf + ++st);
	}
	free(meta_arr);
}

/*
 * Quotes(", ')에 묶인 문자열 처리 함수
 * single quotes인 경우 그냥 내용물 출력
 * double quotes인 경우 $, \ 처리
*/
void	proc_quotes(t_env *root, char **now)
{
	char	*decap_str;
	char	*new_str;
	char	quote;

	if (*now == 0)
		return ;
	decap_str = decap_quotes(*now, &quote);
	if (quote == '\"')
		new_str = proc_metachar(root, decap_str);
	else
		new_str = decap_str;
	free(*now);
	*now = new_str;
}
