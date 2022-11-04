/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:48:53 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/10/15 16:22:59 by cicekyuzbas   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;

	s_len = ft_strlen(s) + 1;
	if (!*s || start >= s_len)
	{
		substr = (char *)malloc(1 * sizeof(char));
		if (!substr)
			return (substr);
		*substr = '\0';
		return (substr);
	}
	if (len + 1 < s_len)
		s_len = len + 1;
	substr = (char *)malloc(s_len * sizeof(char));
	if (!substr)
		return (substr);
	ft_strlcpy(substr, s + start, s_len);
	return (substr);
}
