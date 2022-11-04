/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 17:07:01 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/04 11:28:50 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

// initialize string array and copy envp
void	env_init(char **envp, t_list **new_env)
{
	t_list	*temp;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		temp = ft_lstnew(ft_strdup(envp[i]));
		if (temp == NULL)
		{
			ft_lstclear(new_env, &free);
			return ;
		}
		ft_lstadd_back(new_env, temp);
		i++;
	}
}

// get the value for any env var by name
char	*env_getval(t_list *envp, const char *name, int namelen)
{
	while (envp != NULL && ft_strncmp(envp->content, name, namelen))
		envp = envp->next;
	if (envp != NULL && \
			ft_strchr(envp->content, '=') - (char *)envp->content == namelen)
		return (ft_strchr(envp->content, '=') + 1);
	return (NULL);
}

// set the val of name env var
// name and val are not freed in this function
void	env_setval(t_list **envp, const char *name, const char *val)
{
	t_list	*node;
	char	*new;

	node = *envp;
	while (node != NULL && ft_strncmp(node->content, name, ft_strlen(name)))
		node = node->next;
	if (node == NULL)
		return ;
	new = (char *)malloc((ft_strlen(name) + ft_strlen(val) + 2) * sizeof(char));
	if (new == NULL)
		return ;
	ft_memmove(new, name, ft_strlen(name));
	new[ft_strlen(name)] = '=';
	ft_strlcpy(new + ft_strlen(name) + 1, val, ft_strlen(val) + 1);
	free(node->content);
	node->content = new;
}

//turns linked list to **char
char	**envp_array(t_list *env_lst)
{
	int		i;
	int		lst_size;
	char	**envp;

	lst_size = ft_lstsize(env_lst);
	envp = (char **)malloc(sizeof(envp) * (lst_size + 1));
	if (!envp)
		exit(-1);
	i = 0;
	while (env_lst)
	{
		envp[i] = ft_strdup(env_lst->content);
		i++;
		env_lst = env_lst->next;
	}
	envp[i] = NULL;
	return (envp);
}
