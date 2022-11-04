/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_word.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:08:35 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/03 19:02:30 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

static int	parse_word_append(t_simplecmd *cmd, t_token *tok)
{
	t_list	*node;
	char	*value;

	value = ft_strdup(tok->value);
	if (value == NULL)
		return (12);
	node = ft_lstnew(value);
	if (node == NULL)
	{
		free(value);
		return (12);
	}
	ft_lstadd_back(cmd->arg, node);
	return (0);
}

int	parse_word(t_simplecmd **cmd_table, t_list **tokens)
{
	t_list	*node;
	int		i_cmd;
	int		error;

	if (tokens == NULL)
		return (12);
	if (*tokens == NULL)
		return (0);
	node = *tokens;
	i_cmd = 0;
	error = 0;
	while (node != NULL && !error)
	{
		if (((t_token *)node->content)->type == WORD)
			error = parse_word_append(cmd_table[i_cmd], node->content);
		else if (((t_token *)node->content)->type == PIPE)
			i_cmd++;
		else
			error = 12;
		node = node->next;
	}
	return (error);
}
