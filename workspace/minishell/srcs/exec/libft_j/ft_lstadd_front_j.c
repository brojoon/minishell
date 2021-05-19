/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:17:45 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/20 00:27:48 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_j.h"

void	ft_lstadd_front_j(t_list1 **lst, t_list1 *node)
{
	if (node)
		node->next = *lst;
	*lst = node;
}
