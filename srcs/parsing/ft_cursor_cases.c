/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_cases.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:58:30 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/28 16:00:32 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	change_buf(char **buf, char *str)
{
	ft_memclean(buf, BUFFER_SIZE + 1);
	ft_strlcpy(*buf, str, ft_strlen(str) + 1);
	return (ft_strlen(str));
}


int	proc_cursor_case_up(t_string **now_history,
		t_cursor *cursor, char *prompt, char **buf)
{
	t_string	*target;
	int			ret;

	ret = ft_strlen(*buf);
	if (cursor->history == 0)
		return (ret);
	if (*now_history == 0)
		target = cursor->history;
	else
		target = (*now_history)->prev;
	if (target == 0)
	{
		ft_memclean(buf, BUFFER_SIZE + 1);
		return (ret);
	}
	cursor->hpos = ft_strlen(prompt);
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	tputs(cursor->ce, 1, ft_putchar);
	*now_history = target;
	write(0, target->str, ft_strlen(target->str));
	cursor->hpos = ft_strlen(prompt) + ft_strlen(target->str);
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	ret = change_buf(buf, target->str);
	return (ret);
}

int	proc_cursor_case_down(t_string **now_history,
		t_cursor *cursor, char *prompt, char **buf)
{
	t_string	*target;
	int			ret;

	ret = ft_strlen(*buf);
	if (cursor->history == 0)
		return (ret);
	if (*now_history == 0)
		target = 0;
	else
		target = (*now_history)->next;
	cursor->hpos = ft_strlen(prompt);
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	tputs(cursor->ce, 1, ft_putchar);
	if (target == 0)
	{
		ft_memclean(buf, BUFFER_SIZE + 1);
		return (ret);
	}
	*now_history = target;
	write(0, target->str, ft_strlen(target->str));
	cursor->hpos = ft_strlen(prompt) + ft_strlen(target->str);
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	ret = change_buf(buf, target->str);
	return (ret);
}
