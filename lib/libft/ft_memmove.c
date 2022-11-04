/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:47:29 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:47:31 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*rev_copy(void *dst, const void *src, size_t n)
{
	int	index;

	index = n - 1;
	while (index >= 0)
	{
		*((unsigned char *)dst + index) = *((unsigned char *)src + index);
		index--;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == NULL && src == NULL)
		return (NULL);
	else if (src + len >= dst && src <= dst)
		return (rev_copy(dst, src, len));
	else
		return (ft_memcpy(dst, src, len));
}
