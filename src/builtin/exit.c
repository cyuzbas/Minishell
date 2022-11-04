/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 14:20:54 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/03 12:54:24 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <exec.h>

bool	check_valid_argument(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			return (false);
		i++;
	}
	return (true);
}

void	builtin_exit(t_list *arg, int *exit_code)
{
	if (!arg->next)
	{
		ft_putendl_fd("exit", STDIN_FILENO);
		exit((unsigned char)*exit_code);
	}
	else if (arg->next->next
		&& check_valid_argument((char *)(arg->next->content)))
		print_error("exit: ", NULL, "too many arguments");
	else
	{
		if (!check_valid_argument((char *)(arg->next->content)))
		{
			print_error("exit: ", (char *)(arg->next->content), \
			": numeric argument required");
			*exit_code = 255;
			exit((unsigned char)255);
		}
		*exit_code = ft_atoi((char *)(arg->next->content));
		ft_putendl_fd("exit", STDIN_FILENO);
		exit((unsigned char)*exit_code);
	}
}
