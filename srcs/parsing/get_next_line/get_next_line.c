/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:59:03 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/31 01:44:13 by hyi              ###   ########.fr       */
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
	if ((size_t)idx == ft_strlen(*buf_ref) || g_bash.clean == 1)
		idx = -1;
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

	buf_size = ft_strlen(*buf);
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
			return (buf_size);
		else if (g_bash.clean == 1)
			break ;
		c = 0;
	}
	return (ft_strlen(*buf));
}

int	get_next_line_subloop(int fd, char *prompt,
		t_cursor *cursor, char **buf)
{
	int	flag;
	int	clean_flag;

	clean_flag = get_next_line_sub(prompt, buf, &clean_flag);
	if (clean_flag == 0)
		flag = get_next_line_subsub(fd, prompt, cursor, buf);
	else
		flag = ft_strlen(*buf);
	if (flag == 9999)
		return (9999);
	if (flag > 0 && g_bash.clean == 0)
	{
		if ((*buf)[0] != '\n' && (*buf)[0] != '\0')
		{
			if ((*buf)[flag - 1] == '\n')
				(*buf)[flag - 1] = '\0';
			cursor->history = ft_lstadd_back(&(cursor->history),
					ft_lstinit(ft_strdup(*buf)));
		}
	}
	return (flag);
}

int	get_next_line(int fd, char **line, char *prompt, t_cursor *cursor)
{
	static char	*buf_ref;
	char		*buf;
	int			rd;
	int			flag;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = 0;
	if (get_next_line_sub01(&buf, line, &buf_ref) == 1)
		return (1);
	while (1)
	{
		rd = get_next_line_subloop(fd, prompt, cursor, &buf);
		flag = get_next_line_whilesub(rd, &buf_ref, &buf);
		if (flag == 9999)
			return (flag);
		else if (flag == 1)
			break ;
		if (rd <= 0 || ft_while_loop(line, buf, &buf_ref))
			break ;
	}
	free(buf);
	if (!*line)
		ft_memset(line, 1);
	return (rd);
}
