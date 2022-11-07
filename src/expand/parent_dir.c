/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent_dir.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:31:49 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/04 12:34:51 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*expand_parent_dir(t_list *envp)
{
	char	*pwd;
	char	*tail;
	char	*parent_dir;

	pwd = env_getval(envp, "PWD", 3);
	if (pwd == NULL)
	{
		free(pwd);
		return (NULL);
	}
	tail = pwd + ft_strlen(pwd);
	while (tail > pwd && *tail != '/')
		tail--;
	if (tail != pwd)
		parent_dir = ft_strndup(pwd, tail - pwd);
	else
		parent_dir = ft_strdup("/");
	return (parent_dir);
}

char	*has_expansion(char *str)
{
	int	dqt;
	int	sqt;

	dqt = 0;
	sqt = 0;
	while (*str != '\0')
	{
		if (*str == '\'' && sqt)
			sqt = 0;
		else if (*str == '\'' && !dqt && !sqt \
		&& ft_strchr(str + 1, '\''))
			sqt = 1;
		else if (*str == '"' && dqt)
			dqt = 0;
		else if (*str == '"' && !sqt && !dqt \
		&& ft_strchr(str + 1, '"'))
			dqt = 1;
		else if (*str == '$' && !sqt && (ft_isalnum(str[1]) || str[1] == '?'))
			return (str);
		str++;
	}
	return (NULL);
}
