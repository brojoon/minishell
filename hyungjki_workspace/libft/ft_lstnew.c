/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungjki <hyungjki@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:18:15 by hyungjki          #+#    #+#             */
/*   Updated: 2021/01/02 19:50:17 by hyungjki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list1	*ft_lstnew(void *content)
{
	t_list1	*result;

	result = malloc(sizeof(t_list1));
	if (!result)
		return (NULL);
	result->content = content;
	result->next = NULL;
	return (result);
}
