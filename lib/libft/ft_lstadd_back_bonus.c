/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:46:34 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/19 11:32:04 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*link;

	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		link = *lst;
		while (link->next)
			link = link->next;
		while (new->next)
		{
			link->next = new;
			link = link->next;
			new = new->next;
		}
		link->next = new;
		new->next = NULL;
	}
}
