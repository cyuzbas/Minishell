/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:48:15 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:48:20 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	index;

	index = 0;
	src_len = ft_strlen(src);
	if (!dstsize)
		return (src_len);
	while (index < (dstsize - 1) && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = 0;
	return (src_len);
}
