/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 17:48:50 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/10/24 20:07:02 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_inset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	new_len;
	char	*new_str;

	while (is_inset(*s1, set))
		s1++;
	new_len = ft_strlen(s1);
	if (!new_len)
	{
		new_str = ft_calloc(1, 1);
		return (new_str);
	}
	while (is_inset(s1[new_len - 1], set))
		new_len--;
	new_str = (char *) malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		ft_strlcpy(new_str, s1, new_len + 1);
	return (new_str);
}
