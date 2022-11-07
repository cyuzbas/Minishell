/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:47:10 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:47:12 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*link;
	int		size;

	if (lst == NULL)
		return (0);
	link = lst;
	size = 1;
	while (link->next)
	{
		link = link->next;
		size++;
	}
	return (size);
}
