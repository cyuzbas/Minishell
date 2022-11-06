/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:30:34 by mbatstra          #+#    #+#             */
/*   Updated: 2022/11/05 17:15:23 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_quotes(char *str)
{
	int	numq;

	numq = 0;
	while (*str != '\0')
	{
		if ((*str == '"' || *str == '\'') && ft_strchr(str + 1, *str))
		{
			numq += 2;
			str = ft_strchr(str + 1, *str) + 1;
		}
		else
			str++;
	}
	return (numq);
}

static int	isquote(char c)
{
	return (c == '"' || c == '\'');
}

static int	isclosed(const char *str, char lastq)
{
	return (lastq == '\0' && ft_strchr(str + 1, *str));
}

static void	traverse_quote(char *str, char *qt, int *i, int *offset)
{
	while (isquote(str[*i]) && (isclosed(str + *i, *qt) || *qt == str[*i]))
	{
		if (*qt == str[*i])
			*qt = '\0';
		else
			*qt = str[*i];
		*i += 1;
		*offset += 1;
	}
}

char	*parse_rm_quotes(char *str)
{
	char	*new_str;
	char	lastq;
	int		offset;
	int		i;

	lastq = 0;
	offset = 0;
	i = 0;
	new_str = ft_calloc(ft_strlen(str) - count_quotes(str) + 1, sizeof(char));
	while (str[i] != '\0' && new_str != NULL)
	{
		traverse_quote(str, &lastq, &i, &offset);
		if (str[i] == '\0')
			break ;
		new_str[i - offset] = str[i];
		i++;
	}
	return (new_str);
}
