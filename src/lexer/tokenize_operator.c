/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:02:15 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/04 12:56:07 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

static void	lexer_tokenize_pipe(t_token *token, int *i, t_lexer_flags *flags)
{
	flags->last_exit = lexer_value_append(token, "|", 1);
	*i += 1;
	if (!flags->is_double_quoted && !flags->is_single_quoted)
		flags->is_delim = 1;
}

static void	lexer_tokenize_rdrin(t_token *token, char *cmd, \
								int *i, t_lexer_flags *flags)
{
	if (cmd[*i + 1] == '<')
	{
		flags->last_exit = lexer_value_append(token, "<<", 2);
		*i += 2;
	}
	else
	{
		flags->last_exit = lexer_value_append(token, "<", 1);
		*i += 1;
	}
	if (!flags->is_double_quoted && !flags->is_single_quoted)
		flags->is_delim = 1;
}

static void	lexer_tokenize_rdrout(t_token *token, char *cmd, \
								int *i, t_lexer_flags *flags)
{
	if (cmd[*i + 1] == '>')
	{
		flags->last_exit = lexer_value_append(token, ">>", 2);
		*i += 2;
	}
	else
	{
		flags->last_exit = lexer_value_append(token, ">", 1);
		*i += 1;
	}
	if (!flags->is_double_quoted && !flags->is_single_quoted)
		flags->is_delim = 1;
}

void	lexer_tokenize_operator(t_token *token, char *cmd, \
								int *i, t_lexer_flags *flags)
{
	if (cmd[*i] == '|')
	{
		lexer_tokenize_pipe(token, i, flags);
		return ;
	}
	if (cmd[*i] == '<')
	{
		lexer_tokenize_rdrin(token, cmd, i, flags);
		return ;
	}
	if (cmd[*i] == '>')
	{
		lexer_tokenize_rdrout(token, cmd, i, flags);
		return ;
	}
}
