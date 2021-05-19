/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:17:59 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/02 19:54:36 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_j.h"

void	ft_lstclear_j(t_list1 **lst, void (*del)(void *))
{
	t_list1	*next;
	t_list1	*cur;

	next = *lst;
	while (next)
	{
		cur = next;
		next = cur->next;
		ft_lstdelone_j(cur, del);
	}
	*lst = NULL;
}
