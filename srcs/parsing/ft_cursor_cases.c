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
		return (ret);
	cursor->hpos = ft_strlen(prompt);
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	tputs(cursor->ce, 1, ft_putchar);
	*now_history = target;
	write(0, target->str, ft_strlen(target->str));
	cursor->hpos = ft_strlen(prompt) + ft_strlen(target->str) - 1;
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	ft_memclean(buf, BUFFER_SIZE + 1);
	ft_strlcpy(*buf, target->str, ft_strlen(target->str));
	ret = ft_strlen(target->str);
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
		return (ret);
	*now_history = target;
	write(0, target->str, ft_strlen(target->str));
	cursor->hpos = ft_strlen(prompt) + ft_strlen(target->str) - 1;
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	ft_memclean(buf, BUFFER_SIZE + 1);
	ft_strlcpy(*buf, target->str, ft_strlen(target->str));
	ret = ft_strlen(target->str);
	return (ret);
}
