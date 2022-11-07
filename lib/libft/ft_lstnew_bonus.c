/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:47:06 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/19 12:44:54 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*element;

	if (content == NULL)
		return (NULL);
	element = (t_list *) malloc(sizeof(t_list));
	if (!element)
		return (element);
	element->content = content;
	element->next = 0;
	return (element);
}
