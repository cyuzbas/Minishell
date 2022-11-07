/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_delnode_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:18:46 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/14 17:16:05 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_delnode(t_list **head, t_list *node, void (*del)(void *))
{
	t_list	*temp;

	if (head == NULL || *head == NULL || node == NULL)
		return ;
	if (*head == node)
	{
		*head = node->next;
		ft_lstdelone(node, del);
		return ;
	}
	temp = *head;
	while (temp->next != node && temp->next != NULL)
		temp = temp->next;
	if (temp->next == NULL)
		return ;
	temp->next = node->next;
	ft_lstdelone(node, del);
}
