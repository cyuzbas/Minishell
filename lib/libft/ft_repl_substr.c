/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_repl_substr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:37:13 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/25 13:42:43 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_replsubstr(char *str, char *new_sub, char *old_sub, size_t old_len)
{
	char	*new_str;
	int		new_len;

	new_len = ft_strlen(str) + ft_strlen(new_sub) - old_len;
	new_str = (char *)ft_calloc(new_len + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str, old_sub - str + 1);
	ft_strlcat(new_str, new_sub, ft_strlen(new_str) + ft_strlen(new_sub) + 1);
	ft_strlcat(new_str, old_sub + old_len, new_len + 1);
	return (new_str);
}
