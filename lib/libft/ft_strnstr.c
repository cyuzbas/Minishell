/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:48:44 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:48:46 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	size;
	int		iter;

	size = ft_strlen(needle);
	iter = 0;
	if (!*needle)
		return ((char *)haystack);
	while ((len - iter > size - 1) && *haystack)
	{
		if (!ft_strncmp(haystack, needle, size))
			return ((char *)haystack);
		haystack++;
		iter++;
	}
	return (0);
}
