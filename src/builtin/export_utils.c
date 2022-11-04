/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 15:44:27 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/11/03 13:06:17 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "exec.h"

void	free_spl_nameval(char **spl_nameval)
{
	free(spl_nameval[0]);
	free(spl_nameval[1]);
	free(spl_nameval);
}

int	write_export_env(t_list *envp)
{
	while (envp)
	{
		ft_putstr_fd("declare -x ", 1);
		printf("%s\n", (char *)envp->content);
		envp = envp->next;
	}
	return (0);
}
