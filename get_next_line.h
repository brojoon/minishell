/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 00:28:10 by hyi               #+#    #+#             */
/*   Updated: 2021/05/16 22:01:10 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1024
# define CTRLD 4
# define KEY_LEFT 4479771
# define KEY_RIGHT 4414235
# define KEY_UP 4283163
# define KEY_DOWN 4348699
# define ESC 127
# include <termios.h>
# include <termcap.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_cursor
{
	struct termios term;
	char *cm;
	char *ce;
	int hpos;
	int vpos;
}				t_cursor;
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
int		get_next_line(int fd, char **line, char *prompt, t_cursor *cursor);
#endif
