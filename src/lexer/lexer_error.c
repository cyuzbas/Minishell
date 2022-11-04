/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_error.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 21:06:45 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/03 18:59:54 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"
#include "exec.h"

// errors:
// redirs with invalid operand
// pipes with invalid operands
// what else?

static int	lexer_error_redir(t_list *tokens)
{
	while (tokens != NULL)
	{
		if (((t_token *)tokens->content)->type < PIPE)
		{
			if (tokens->next == NULL)
			{
				ft_putstr_fd \
				("minishell: syntax error near unexpected token `newline'\n", 2);
				return (2);
			}
			else if (((t_token *)tokens->next->content)->type != WORD)
			{
				ft_putstr_fd \
				("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd(((t_token *)tokens->next->content)->value, 2);
				ft_putstr_fd("'\n", 2);
				return (258);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

static int	lexer_iter_pipes(t_list *tokens)
{
	while (tokens->next != NULL)
	{
		if (((t_token *)tokens->next->content)->type == PIPE)
		{
			if (((t_token *)tokens->content)->type != WORD || \
				tokens->next->next == NULL)
			{
				ft_putstr_fd \
				("minishell: syntax error near unexpected token `newline'\n", 2);
				return (258);
			}
			else if (((t_token *)tokens->content)->type != WORD || \
					((t_token *)tokens->next->next->content)->type == PIPE)
			{
				ft_putstr_fd \
				("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd(((t_token *)tokens->next->content)->value, 2);
				ft_putstr_fd("'\n", 2);
				return (258);
			}
		}
		tokens = tokens->next;
	}
	return (0);
}

static int	lexer_error_pipe(t_list *tokens)
{
	if (tokens == NULL)
		return (0);
	if (((t_token *)tokens->content)->type == PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (258);
	}
	return (lexer_iter_pipes(tokens));
}

int	lexer_error(t_list *tokens)
{
	int	error;

	error = lexer_error_redir(tokens);
	if (!error)
		error = lexer_error_pipe(tokens);
	return (error);
}
