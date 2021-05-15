/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 00:28:24 by hyi               #+#    #+#             */
/*   Updated: 2021/05/02 17:30:03 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen1(char *str)
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
		*buf_ref = (idx + 1 < ft_strlen1(buf) && *(buf + idx + 1))
			? ft_strdup1(&buf[idx + 1]) : 0;
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
		*buf_ref = (idx + 1 < ft_strlen1(*buf_ref) && *(*buf_ref + idx + 1))
			? ft_strdup1(*buf_ref + idx + 1) : 0;
		ret = 1;
	}
	else
	{
		ft_resize_and_copy(line, *buf_ref, 0, ft_strlen1(*buf_ref));
		*buf_ref = 0;
		ret = 0;
	}
	free(del);
	return (ret);
}

int	get_next_line(int fd, char **line, char *prompt)
{
	static char	*buf_ref;
	char		*buf;
	ssize_t		rd;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = 0;
	if (buf_ref)
		if (ft_proc_buf_ref(line, &buf_ref))
			return (1);
	ft_memset1(&buf, BUFFER_SIZE + 1);
	while (1){
		write(0, prompt, ft_strlen1(prompt));
		if ((rd = read(fd, buf, BUFFER_SIZE)) <= 0)
			break ;
		if (ft_while_loop(line, buf, &buf_ref))
			break ;
	}
	free(buf);
	if (!*line)
		ft_memset1(line, 1);
	if (rd > 0)
		return (1);
	return (rd < 0 ? -1 : 0);
}
