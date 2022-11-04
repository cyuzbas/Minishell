/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:48:06 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/26 18:15:41 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*catstr;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	catstr = (char *)malloc(size * sizeof(char));
	if (!catstr)
		return (catstr);
	ft_strlcpy(catstr, s1, size);
	ft_strlcat(catstr, s2, size);
	return (catstr);
}
