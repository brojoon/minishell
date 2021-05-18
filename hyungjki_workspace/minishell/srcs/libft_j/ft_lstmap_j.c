/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:18:11 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/02 18:18:22 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_j.h"

t_list1	*ft_lstmap_j(t_list1 *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list1	*new;
	t_list1	*start;

	start = NULL;
	while (lst)
	{
		new = ft_lstnew_j(f(lst->content));
		if (!new)
		{
			ft_lstclear_j(&start, del);
			return (NULL);
		}
		ft_lstadd_back_j(&start, new);
		lst = lst->next;
	}
	return (start);
}
