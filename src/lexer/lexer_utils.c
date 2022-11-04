/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 19:22:51 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/03 19:00:28 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

int	lexer_is_operator_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	lexer_value_append(t_token *token, char *value, int val_len)
{
	char	*new;

	new = (char *)malloc(ft_strlen(token->value) + val_len + 1);
	if (new == NULL)
		return (12);
	ft_strlcpy(new, token->value, ft_strlen(token->value) + 1);
	ft_strlcat(new, value, ft_strlen(token->value) + val_len + 1);
	free(token->value);
	token->value = new;
	return (0);
}

t_token	*lexer_token_copy(t_token *token)
{
	t_token	*new_token;

	if (token == NULL)
		return (NULL);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = ft_strdup(token->value);
	if (new_token->value == NULL)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = token->type;
	return (new_token);
}

void	lexer_token_identifier(t_token *token)
{
	if (token->value[0] == '<')
	{
		if (ft_strlen(token->value) == 1)
			token->type = RDR_IN;
		else
			token->type = HEREDOC;
	}
	else if (token->value[0] == '>')
	{
		if (ft_strlen(token->value) == 1)
			token->type = RDR_OUT;
		else
			token->type = RDR_APP;
	}
	else if (token->value[0] == '|')
		token->type = PIPE;
	else
		token->type = WORD;
}

void	lexer_clear_token(void *token)
{
	free(((t_token *)token)->value);
	free(token);
}
