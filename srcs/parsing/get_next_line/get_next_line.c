/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:59:03 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 12:59:04 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((size_t)idx + 1 < ft_strlen(buf) && *(buf + idx + 1))
			*buf_ref = ft_strdup(&buf[idx + 1]);
		else
			*buf_ref = 0;
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
		if ((size_t)idx + 1 < ft_strlen(*buf_ref) && *(*buf_ref + idx + 1))
			*buf_ref = ft_strdup(*buf_ref + idx + 1);
		else
			*buf_ref = 0;
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

int	get_next_line_subsub(int fd, char *prompt,
		t_cursor *cursor, char **buf)
{
	int		c;
	int		buf_size;
	int		rd;

	buf_size = 0;
	c = 0;
	while (1)
	{
		rd = read(fd, &c, sizeof(c));
		if (rd <= 0)
			return (rd);
		update_cursor_pos(cursor);
		buf_size = proc_cursor(cursor, c, prompt, buf);
		if (buf_size == -1)
		{
			free(prompt);
			return (9999);
		}
		else if (buf_size == BUFFER_SIZE || (*buf)[buf_size - 1] == '\n')
		{
			if ((*buf)[buf_size - 1] == '\n')
				(*buf)[buf_size - 1] = '\0';
			return (rd);
		}
		c = 0;
	}
	return (rd);
}

int	get_next_line_subloop(int fd, char *prompt,
		t_cursor *cursor, char **buf)
{
	int	flag;

	write(0, prompt, ft_strlen(prompt));
	flag = get_next_line_subsub(fd, prompt, cursor, buf);
	if (flag == 9999)
		return (9999);
	if (flag > 0 && (*buf)[0] != '\n')
		cursor->history = ft_lstadd_back(&(cursor->history),
				ft_lstinit(ft_strdup(*buf)));
	return (flag);
}

int	get_next_line(int fd, char **line, char *prompt, t_cursor *cursor)
{
	static char	*buf_ref;
	char		*buf;
	int			rd;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = 0;
	if (buf_ref && ft_proc_buf_ref(line, &buf_ref))
		return (1);
	ft_memset(&buf, BUFFER_SIZE + 1);
	while (1)
	{
		rd = get_next_line_subloop(fd, prompt, cursor, &buf);
		if (rd == 9999)
		{
			free(buf);
			return (9999);
		}
		else if (rd <= 0 || ft_while_loop(line, buf, &buf_ref))
			break ;
	}
	free(buf);
	if (!*line)
		ft_memset(line, 1);
	return (rd);
}
