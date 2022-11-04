/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:06:19 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/14 17:09:49 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

// in parsing context redirections are stored as tokens where
// type is the operator and value the operand/argument

static int	add_rdr_to_cmd(t_simplecmd *cmd, t_token *tok)
{
	t_list	*node;

	node = ft_lstnew(tok);
	if (node == NULL)
		return (1);
	if (tok->type < RDR_OUT)
		ft_lstadd_back(cmd->in, node);
	else
		ft_lstadd_back(cmd->out, node);
	return (0);
}

static int	append_rdr(t_list **current, t_list **tokens, t_simplecmd *cmd)
{
	t_token	*new_tok;
	t_list	*skip;
	int		error;

	new_tok = lexer_token_copy((*current)->next->content);
	if (new_tok == NULL)
		return (1);
	new_tok->type = ((t_token *)(*current)->content)->type;
	error = add_rdr_to_cmd(cmd, new_tok);
	skip = (*current)->next->next;
	ft_lst_delnode(tokens, (*current)->next, &lexer_clear_token);
	ft_lst_delnode(tokens, (*current), &lexer_clear_token);
	(*current) = skip;
	return (error);
}

int	parse_redir(t_simplecmd **cmd_table, t_list **tokens)
{	
	t_list	*current;
	int		error;
	int		i_cmd;

	current = *tokens;
	error = 0;
	i_cmd = 0;
	while (current != NULL && current->next != NULL && !error)
	{
		if (((t_token *)current->content)->type == PIPE)
			i_cmd++;
		if (((t_token *)current->content)->type < PIPE)
			error = append_rdr(&current, tokens, cmd_table[i_cmd]);
		else
			current = current->next;
	}
	return (error);
}
