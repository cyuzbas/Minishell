/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:48:47 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:48:49 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*temp;

	temp = s + ft_strlen(s);
	while (temp >= s)
	{
		if (*temp == (char) c)
			return ((char *) temp);
		temp--;
	}
	return (0);
}
