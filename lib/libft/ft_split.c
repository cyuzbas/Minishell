/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:47:53 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/06 17:47:55 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	lenchr(char const *str, char c)
{
	size_t	ret_val;

	ret_val = 0;
	while (*str)
	{
		if (*str == c)
			return (ret_val);
		ret_val++;
		str++;
	}
	return (ret_val);
}

size_t	num_words(char const *str, char c)
{
	size_t	words;
	int		is_delim;

	words = 0;
	is_delim = 1;
	while (*str)
	{
		if (is_delim && *str != c)
		{
			words++;
			is_delim = 0;
		}
		if (!is_delim && *str == c)
			is_delim = 1;
		str++;
	}
	return (words);
}

void	*del_lst(char **split_arr)
{
	size_t	index;

	index = 0;
	while (split_arr[index])
	{
		free(split_arr[index]);
		index++;
	}
	free(split_arr[index]);
	free(split_arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	arr_size;
	size_t	str_size;
	size_t	index;
	char	**split_arr;

	arr_size = num_words(s, c) + 1;
	split_arr = (char **) malloc(arr_size * sizeof(char *));
	if (!split_arr)
		return (split_arr);
	index = 0;
	while (index < arr_size - 1)
	{
		while (*s == c)
			s++;
		str_size = lenchr(s, c);
		split_arr[index] = ft_strndup(s, str_size);
		if (!split_arr[index])
			return (del_lst(split_arr));
		s += str_size;
		index++;
	}
	split_arr[index] = NULL;
	return (split_arr);
}
