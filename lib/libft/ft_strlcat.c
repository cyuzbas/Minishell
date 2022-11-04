/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:48:09 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:48:13 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	index_dst;
	size_t	index_src;

	index_dst = 0;
	index_src = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	index_dst = dst_len;
	while ((index_src < dstsize - dst_len - 1) && src[index_src])
	{
		dst[index_dst] = src[index_src];
		index_dst++;
		index_src++;
	}
	if (dstsize)
		dst[index_dst] = 0;
	return (dst_len + src_len);
}
