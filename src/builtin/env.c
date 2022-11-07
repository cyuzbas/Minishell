/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 14:22:40 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/03 13:29:10 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	builtin_env(t_list *envp)
{
	while (envp != NULL)
	{
		if (printf("%s\n", (char *)envp->content) < 0)
			return (1);
		envp = envp->next;
	}
	return (0);
}
