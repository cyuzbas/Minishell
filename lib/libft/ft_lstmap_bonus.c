/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:46:55 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:47:02 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))

{
	t_list	*start;
	t_list	*new;
	t_list	*temp;

	temp = lst;
	new = ft_lstnew(f(temp->content));
	if (new == NULL)
		return (NULL);
	start = new;
	while (temp->next != NULL)
	{
		temp = temp->next;
		new->next = ft_lstnew(f(temp->content));
		if (new->next == NULL)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		new = new->next;
	}
	return (start);
}
