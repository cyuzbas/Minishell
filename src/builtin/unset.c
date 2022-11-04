/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 15:11:42 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/03 17:09:16 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static int	invalid_name(char *name)
{
	int			i;

	i = 0;
	while (name[i])
	{
		if (ft_isdigit(name[0]) || \
		(!ft_isalnum(name[i]) && name[i] != '_'))
		{
			print_error("unset: `", name, "': not a valid identifier");
			g_mini.exit_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

// check proper name length in order to not match similar-starting names
static void	match_node(t_list **node, t_list **prev, char *name)
{
	unsigned long	temp_namelen;

	while (*node != NULL)
	{
		temp_namelen = (void *)ft_strchr((*node)->content, '=') - \
					(*node)->content;
		if (temp_namelen < ft_strlen(name))
			temp_namelen = ft_strlen(name);
		if (!ft_strncmp((*node)->content, name, temp_namelen))
			break ;
		*prev = *node;
		*node = (*node)->next;
	}
}

int	builtin_unset(t_list **envp, t_list *arg)
{
	t_list	*node;
	t_list	*prev;
	char	*name;

	if (!arg->next)
		return (1);
	while (arg->next != NULL)
	{
		name = (char *)(arg->next->content);
		arg = arg->next;
		if (invalid_name(name))
			continue ;
		node = *envp;
		prev = *envp;
		match_node(&node, &prev, name);
		if (node == NULL)
			return (0);
		else if (node == prev)
			(*envp)->next = node->next;
		else
			prev->next = node->next;
		ft_lstdelone(node, &free);
	}
	return (g_mini.exit_code);
}
