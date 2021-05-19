/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:17:33 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/20 00:27:49 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_j.h"

void	ft_lstadd_back_j(t_list1 **lst, t_list1 *node)
{
	t_list1		*tmp;

	tmp = ft_lstlast_j(*lst);
	if (tmp)
		tmp->next = node;
	else
		*lst = node;
}