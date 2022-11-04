/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:06:07 by mbatstra          #+#    #+#             */
/*   Updated: 2022/10/14 13:06:11 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

static void	parse_clear_cmd(t_simplecmd *cmd)
{
	ft_lstclear(cmd->arg, &free);
	ft_lstclear(cmd->in, &lexer_clear_token);
	ft_lstclear(cmd->out, &lexer_clear_token);
	free(cmd->arg);
	free(cmd->in);
	free(cmd->out);
	free(cmd);
}

static t_simplecmd	*parse_simplecmd_init(void)
{
	t_simplecmd	*cmd;

	cmd = (t_simplecmd *)malloc(sizeof(t_simplecmd));
	if (cmd == NULL)
		return (NULL);
	cmd->arg = (t_list **)malloc(sizeof(t_list *));
	cmd->in = (t_list **)malloc(sizeof(t_list *));
	cmd->out = (t_list **)malloc(sizeof(t_list *));
	if (cmd->arg == NULL || cmd->in == NULL || cmd->out == NULL)
	{
		parse_clear_cmd(cmd);
		return (NULL);
	}
	*(cmd->arg) = NULL;
	*(cmd->in) = NULL;
	*(cmd->out) = NULL;
	return (cmd);
}

void	parse_clear_cmd_table(t_simplecmd **cmd_table)
{
	int	i;

	i = 0;
	while (cmd_table[i] != NULL)
	{
		parse_clear_cmd(cmd_table[i]);
		i++;
	}
	free(cmd_table);
}

static int	parse_count_pipes(t_list *tokens)
{
	int	numpipes;

	numpipes = 0;
	while (tokens != NULL)
	{
		if (((t_token *)tokens->content)->type == PIPE)
			numpipes++;
		tokens = tokens->next;
	}
	return (numpipes);
}

t_simplecmd	**parse_cmd_init(t_list *tokens)
{
	t_simplecmd	**cmd_table;
	int			numpipes;
	int			i;

	numpipes = parse_count_pipes(tokens);
	cmd_table = (t_simplecmd **)malloc((numpipes + 2) * sizeof(t_simplecmd *));
	if (cmd_table == NULL)
		return (NULL);
	i = 0;
	while (i < numpipes + 1)
	{
		cmd_table[i] = parse_simplecmd_init();
		if (cmd_table[i] == NULL)
		{
			parse_clear_cmd_table(cmd_table);
			return (NULL);
		}
		i++;
	}
	cmd_table[i] = NULL;
	return (cmd_table);
}
