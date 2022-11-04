/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:46:41 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/13 17:37:33 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		free(*lst);
		return ;
	}
	node = *lst;
	next = node->next;
	while (node != NULL)
	{
		del(node->content);
		free(node);
		node = next;
		if (next != NULL)
			next = next->next;
	}
}
