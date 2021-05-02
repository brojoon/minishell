/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 00:28:10 by hyi               #+#    #+#             */
/*   Updated: 2021/05/02 17:34:27 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1024
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

/*
** get_next_line_utils.c
*/
int		ft_memset(char **line, size_t size);
int		ft_get_next_idx(char *buf, char c, int st);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_resize_and_copy(char **line, char *buf, int st, int ed);
char	*ft_strdup(char *str);
/*
** get_next_line.c
*/
int		ft_strlen(char *str);
int		ft_while_loop(char **line, char *buf, char **buf_ref);
int		ft_proc_buf_ref(char **line, char **buf_ref);
int		get_next_line(int fd, char **line, char *prompt);
#endif
