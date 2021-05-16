/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 00:28:24 by hyi               #+#    #+#             */
/*   Updated: 2021/05/16 21:25:59 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	st;

	if (!str || !*str)
		return (0);
	st = 0;
	while (str[st])
		st++;
	return (st);
}

int	ft_while_loop(char **line, char *buf, char **buf_ref)
{
	int	idx;
	int	st;

	idx = ft_get_next_idx(buf, '\n', 0);
	if (idx < 0)
		ft_resize_and_copy(line, buf, 0, BUFFER_SIZE);
	else
	{
		ft_resize_and_copy(line, buf, 0, idx);
		*buf_ref = (idx + 1 < ft_strlen(buf) && *(buf + idx + 1))
			? ft_strdup(&buf[idx + 1]) : 0;
		return (1);
	}
	st = 0;
	while (st < BUFFER_SIZE)
		buf[st++] = '\0';
	return (0);
}

int	ft_proc_buf_ref(char **line, char **buf_ref)
{
	int		idx;
	char	*del;
	int		ret;

	idx = ft_get_next_idx(*buf_ref, '\n', 0);
	del = *buf_ref;
	if (idx >= 0)
	{
		ft_resize_and_copy(line, *buf_ref, 0, idx);
		*buf_ref = (idx + 1 < ft_strlen(*buf_ref) && *(*buf_ref + idx + 1))
			? ft_strdup(*buf_ref + idx + 1) : 0;
		ret = 1;
	}
	else
	{
		ft_resize_and_copy(line, *buf_ref, 0, ft_strlen(*buf_ref));
		*buf_ref = 0;
		ret = 0;
	}
	free(del);
	return (ret);
}

int	nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	ft_make_int(const char *ptr, int st, int ed, int sign)
{
	unsigned long	ret;
	unsigned long	mod;

	ret = 0;
	mod = 1;
	while (--ed >= st)
	{
		ret += ((unsigned long)(ptr[ed] - '0') * mod);
		mod *= 10;
	}
	if (ret > 2147483647 && sign == 1)
		return (-1);
	else if (ret > 2147483648 && sign == -1)
		return (0);
	return (ret * sign);
}


int	ft_atoi(const char *nptr)
{
	int		st;
	int		ed;
	int		sign;

	sign = 1;
	st = 0;
	while (nptr[st] && (nptr[st] == ' ' ||
				(nptr[st] >= 0x09 && nptr[st] <= 0x0D)))
		st++;
	if (!nptr[st])
		return (0);
	if (nptr[st] == '-')
		sign = -1;
	if (sign == -1 || nptr[st] == '+')
		st++;
	if (nptr[st] < '0' || nptr[st] > '9')
		return (0);
	ed = st;
	while (nptr[ed] >= '0' && nptr[ed] <= '9')
		ed++;
	return (ft_make_int(nptr, st, ed, sign));
}

void update_cursor_pos(t_cursor *cursor)
{
	int		a = 0;
	int		i = 1;
	char	buf[255];
	int		ret;
	int		temp;

	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				cursor->vpos = ft_atoi(&buf[i]) - 1;
			else
			{
				temp = ft_atoi(&buf[i]);
				cursor->hpos = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}

int ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int cursor_mvleft(t_cursor *cursor, int hpos_min)
{
	if (cursor->hpos <= hpos_min)
		return (1);
	cursor->hpos--;
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	return (0);
}

int cursor_mvright(t_cursor *cursor, int hpos_max)
{
	if (cursor->hpos >= hpos_max)
		return (1);
	cursor->hpos++;
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	return (0);
}

int cursor_erase(t_cursor *cursor, int hpos_min)
{
	if (cursor->hpos <= hpos_min)
		return (1);
	cursor->hpos--;
	tputs(tgoto(cursor->cm, cursor->hpos, cursor->vpos), 1, ft_putchar);
	tputs(cursor->ce, 1, ft_putchar);

	return (0);
}

int cursor_move(t_cursor *cursor, int flag, int hpos_min, char *buf)
{
	int	ret;

	ret = ft_strlen(buf);
	if (flag == KEY_LEFT)
		cursor_mvleft(cursor, hpos_min);
	else if(flag == KEY_RIGHT)
		cursor_mvright(cursor, hpos_min + ft_strlen(buf));
	else if (flag == KEY_UP || flag == KEY_DOWN)
		;
	else if (flag == ESC)
	{
		if (cursor_erase(cursor, hpos_min) == 0)
			buf[ret--] = 0;
	}
	else
	{
		buf[ret++] = (char)flag;
		write(0, &flag, 1);
	}
	return (ret);
}

int	get_next_line(int fd, char **line, char *prompt, t_cursor *cursor)
{
	static char	*buf_ref;
	char		*buf;
	ssize_t		rd;
	int			c;
	int			buf_size;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = 0;
	if (buf_ref)
		if (ft_proc_buf_ref(line, &buf_ref))
			return (1);
	ft_memset(&buf, BUFFER_SIZE + 1);
	buf_size = 0;
	while (1)
	{
		write(0, prompt, ft_strlen(prompt));
		c = 0;
		while((rd = read(fd, &c, sizeof(c))) > 0)
		{
			update_cursor_pos(cursor);
			buf_size = cursor_move(cursor, c, ft_strlen(prompt), buf);
			if (buf_size == BUFFER_SIZE || buf[buf_size - 1] == '\n')
				break ;
			c = 0;
		}
		if (rd <= 0)
			break ;
		if (ft_while_loop(line, buf, &buf_ref))
			break ;
	}
	free(buf);
	if (!*line)
		ft_memset(line, 1);
	if (rd > 0)
		return (1);
	return (rd < 0 ? -1 : 0);
}
