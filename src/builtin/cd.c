/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/15 15:18:51 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/04 12:48:53 by mbatstra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"
#include "exec.h"

int	builtin_cd(char *path, t_list **envp)
{
	char	*new_path;

	new_path = NULL;
	if (path == NULL)
		new_path = ft_strdup(env_getval(*envp, "HOME", 4));
	else
		new_path = ft_strdup(path);
	if (new_path == NULL)
		return (1);
	if (chdir(new_path) != 0)
	{
		perror("cd");
		return (1);
	}
	env_setval(envp, "OLDPWD", env_getval(*envp, "PWD", 3));
	free(new_path);
	new_path = getcwd(NULL, 1);
	if (new_path == NULL)
	{
		perror("cd");
		return (1);
	}
	env_setval(envp, "PWD", new_path);
	free(new_path);
	return (0);
}
