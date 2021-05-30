/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:58:16 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/30 21:42:42 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_memclean(char **buf, int size)
{
	int	st;

	st = 0;
	while (st < size)
		(*buf)[st++] = 0;
}

int		proc_cursor(t_cursor *cursor, int flag, char *prompt, char **buf)
{
	static t_string	*now_history;

	if (flag == KEY_UP)
		return (proc_cursor_case_up(&now_history, cursor, prompt, buf));
	else if (flag == KEY_DOWN)
		return (proc_cursor_case_down(&now_history, cursor, prompt, buf));
	else if (flag == ESC)
		cursor_erase(cursor, ft_strlen(prompt), *buf);
	else if (flag == CTRLD)
	{
		if (ft_strlen(*buf) == 0)
			return (-1);
	}
	else
	{
		now_history = 0;
		(*buf)[ft_strlen(*buf)] = (char)flag;
		write(0, &flag, 1);
	}
	return (ft_strlen(*buf));
}

/*
** \033[6n의 결과로 먼저 나오는 숫자가 row, 뒤에 나오는 숫자가 col
** order_flag == 0 -> row, order_flag == 1 -> col
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
