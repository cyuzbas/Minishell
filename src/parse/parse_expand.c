/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_expand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 16:20:25 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/04 11:55:51 by mbatstra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "exec.h"
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

static void	rm_quote_init_vars(char *lastq, int *offset)
{
	*lastq = 0;
	*offset = 0;
}

static char	*parse_rm_quotes(char *str, int i)
{
	char	*new_str;
	char	lastq;
	int		offset;

	rm_quote_init_vars(&lastq, &offset);
	new_str = ft_calloc(ft_strlen(str) - count_quotes(str) + 1, sizeof(char));
	while (str[i] != '\0' && new_str != NULL)
	{
		while ((str[i] == '"' || str[i] == '\'') && \
			((lastq == '\0' && ft_strchr(str + i + 1, str[i])) \
			|| lastq == str[i]))
		{
			if (lastq == str[i])
				lastq = '\0';
			else
				lastq = str[i];
			i++;
			offset++;
		}
		if (str[i] == '\0')
			break ;
		new_str[i - offset] = str[i];
		i++;
	}
	return (new_str);
}

char	*parse_expand_env(char *old_val, t_list *envp)
{
	char	*dllr;
	char	*new_val;
	char	*new_sub;
	int		old_sublen;

	if (old_val == NULL)
		return (NULL);
	old_sublen = 1;
	dllr = has_expansion(old_val);
	if (dllr == NULL)
		return (old_val);
	while (ft_isalnum(dllr[old_sublen]) || dllr[old_sublen] == '_')
		old_sublen++;
	if (dllr[1] == '?')
		return (ft_itoa(g_mini.exit_code));
	new_sub = env_getval(envp, dllr + 1, old_sublen - 1);
	new_val = ft_replsubstr(old_val, new_sub, dllr, old_sublen);
	if (new_val == NULL)
		return (NULL);
	return (parse_expand_env(new_val, envp));
}

int	parse_expand(t_list *tokens, t_list *env)
{
	t_token	*tok;
	char	*new_val;

	while (tokens != NULL)
	{
		tok = ((t_token *)tokens->content);
		if (tok->type == WORD)
		{
			new_val = parse_expand_env(tok->value, env);
			if (new_val == NULL)
				return (1);
			if (new_val != tok->value)
			{
				free(tok->value);
				tok->value = new_val;
			}
			new_val = parse_rm_quotes(tok->value, 0);
			if (new_val == NULL)
				return (1);
			free(tok->value);
			tok->value = new_val;
		}
		tokens = tokens->next;
	}
	return (0);
}
