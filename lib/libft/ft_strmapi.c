/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:48:30 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:48:33 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	index;
	char	*new_str;

	len = ft_strlen(s);
	index = 0;
	new_str = (char *) malloc(len * sizeof(char) + 1);
	if (!new_str)
		return (new_str);
	while (*s)
	{
		new_str[index] = f(index, *s);
		index++;
		s++;
	}
	new_str[index] = 0;
	return (new_str);
}
