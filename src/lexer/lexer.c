/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:22:08 by mbatstra          #+#    #+#             */
/*   Updated: 2022/11/01 15:32:53 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

static t_token	*init_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->value = NULL;
	return (token);
}

static void	init_flags(t_lexer_flags *flags)
{
	flags->is_double_quoted = 0;
	flags->is_single_quoted = 0;
	flags->is_delim = 0;
	flags->last_exit = 0;
}

static void	delimit(t_list **tokens, t_token **token, t_lexer_flags *flags)
{
	t_list	*new;

	if (flags->last_exit)
	{
		ft_lstclear(tokens, &lexer_clear_token);
		lexer_clear_token(*token);
	}
	if (flags->is_delim)
	{
		if (ft_strlen((*token)->value) == 0)
			lexer_clear_token(*token);
		else
		{
			lexer_token_identifier(*token);
			new = ft_lstnew(*token);
			ft_lstadd_back(tokens, new);
		}
		*token = init_token();
		init_flags(flags);
	}
}

int	lexer_tokenize(t_list **tokens, char *cmd_line)
{
	t_lexer_flags	flags;
	t_token			*token;
	int				i;

	i = 0;
	token = init_token();
	if (token == NULL)
		return (1);
	init_flags(&flags);
	while (cmd_line[i] != '\0' && !flags.last_exit)
	{
		if (lexer_is_operator_char(cmd_line[i]))
			lexer_tokenize_operator(token, cmd_line, &i, &flags);
		else
			lexer_tokenize_word(token, cmd_line, &i, &flags);
		delimit(tokens, &token, &flags);
	}
	if (!flags.last_exit)
		flags.last_exit = lexer_error(*tokens);
	lexer_clear_token(token);
	return (flags.last_exit);
}
