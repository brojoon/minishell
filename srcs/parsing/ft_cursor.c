#include "minishell.h"

int	cursor_mvleft(t_cursor *cursor, int hpos_min)
{
	if (cursor->hpos <= hpos_min)
		return (1);
	cursor->hpos--;
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	return (0);
}

int	cursor_mvright(t_cursor *cursor, int hpos_max)
{
	if (cursor->hpos >= hpos_max)
		return (1);
	cursor->hpos++;
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	return (0);
}

int	cursor_erase(t_cursor *cursor, int hpos_min, char *buf)
{
	int	st;

	if (cursor->hpos <= hpos_min)
		return (1);
	cursor->hpos--;
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	tputs(cursor->ce, 1, ft_putchar);
	st = ft_strlen(buf) - 1;
	while (buf[st])
		buf[st++] = 0;
	return (0);
}

int	proc_cursor(t_cursor *cursor, int flag, int hpos_min, char *buf)
{
	int	ret;

	ret = ft_strlen(buf);
	if (flag == KEY_LEFT)
		cursor_mvleft(cursor, hpos_min);
	else if (flag == KEY_RIGHT)
		cursor_mvright(cursor, hpos_min + ft_strlen(buf));
	else if (flag == KEY_UP || flag == KEY_DOWN)
		;
	else if (flag == ESC)
		cursor_erase(cursor, hpos_min, buf);
	else if (flag == CTRLD)
	{
		if (ret == 0)
			return (-1);
	}
	else
	{
		buf[ret++] = (char)flag;
		write(0, &flag, 1);
	}
	return (ret);
}

/*
 * \033[6n의 결과로 먼저 나오는 숫자가 row, 뒤에 나오는 숫자가 col
 * order_flag == 0 -> row, order_flag == 1 -> col
*/
void	update_cursor_pos(t_cursor *cursor)
{
	char	buf[255];
	int		num;
	int		st;
	int		rd;
	int		order_flag;

	write(0, "\033[6n", 4);
	rd = read(0, buf, 254);
	buf[rd] = '\0';
	st = 1;
	order_flag = 0;
	while (buf[st])
	{
		if (buf[st] >= '0' && buf[st] <= '9')
		{
			num = ft_atoi(&buf[st]) - 1;
			if (order_flag == 0)
				cursor->vpos = num;
			else
				cursor->hpos = num;
			order_flag++;
			st += nbr_length(num) - 1;
		}
		st++;
	}
}
