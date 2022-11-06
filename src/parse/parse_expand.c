/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 16:20:25 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/05 17:44:05 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "exec.h"
#include "libft.h"

char	*parse_expand_env(char *old_val, t_list *envp)
{
	char	*dllr;
	char	*new_val;
	char	*new_sub;
	int		len;

	if (old_val == NULL)
		return (NULL);
	dllr = has_expansion(old_val);
	if (dllr == NULL)
		return (old_val);
	len = 1;
	while (ft_isalnum(dllr[len]) || dllr[len] == '_' || dllr[len] == '?')
		len++;
	if (dllr[1] == '?')
		new_sub = (ft_itoa(g_mini.exit_code));
	else
		new_sub = ft_strdup(env_getval(envp, dllr + 1, len - 1));
	if (new_sub == NULL)
		return (NULL);
	new_val = ft_replsubstr(old_val, new_sub, dllr, len);
	free(new_sub);
	free(old_val);
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
			if (new_val != tok->value)
			{
				tok->value = new_val;
				if (new_val == NULL)
					return (12);
			}
			new_val = parse_rm_quotes(tok->value);
			if (new_val == NULL)
				return (12);
			free(tok->value);
			tok->value = new_val;
		}
		tokens = tokens->next;
	}
	return (0);
}
