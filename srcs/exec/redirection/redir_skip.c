/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_skip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:21:15 by hyungjki          #+#    #+#             */
/*   Updated: 2021/05/24 13:21:16 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		redir_cmp(t_string *s1, t_string *s2)
{
	int		type1;
	int		type2;

	type1 = get_redir_type(s1);
	type2 = get_redir_type(s2);
	if (type1 == RIGHT || type1 == DRIGHT)
	{
		if (type2 == RIGHT || type2 == DRIGHT)
			return (1);
	}
	if (type1 == LEFT && type2 == LEFT)
		return (1);
	return (0);
}

int		redir_skip_left(char *str)
{
	char	*filename;
	int		fd;

	filename = str;
	fd = open(filename, O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("bash: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putendl_fd(" No such file or directory", STDERR_FILENO);
		g_bash.status = 2;
		return (-1);
	}
	close(fd);
	return (0);
}

int		redir_skip_right(char *str)
{
	char	*filename;
	int		fd;

	filename = str;
	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	close(fd);
	return (0);
}

void	handle_redir_right(t_string *rd)
{
	int		fd;
	int		ret;
	int		type;

	while (rd != NULL && rd->next
		&& rd->next->next && rd->next->next->next \
		&& redir_cmp(rd, rd->next->next))
	{
		if (get_redir_type(rd) == RIGHT || \
			get_redir_type(rd) == DRIGHT)
			ret = redir_skip_right(rd->next->str);
		else if (get_redir_type(rd) == LEFT)
			ret = redir_skip_left(rd->next->str);
		if (ret == -1)
			return ;
		rd = rd->next->next;
	}
	printf("here2");
	type = get_redir_type(rd);
	if (type == RIGHT)
		fd = open(rd->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(rd->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
}
