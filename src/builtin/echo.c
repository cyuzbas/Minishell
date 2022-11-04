/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 14:16:25 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/04 15:46:28 by mbatstra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "exec.h"

void	write_echo(t_list *arg, int i)
{
	char	*command;
	int		x;

	while (i > 0)
	{
		arg = arg->next;
		i--;
	}
	while (arg)
	{
		command = (char *)(arg->content);
		x = 0;
		if (ft_strcmp("\"\"", command) != 0)
		{
			while (command[x])
			{
				ft_putchar_fd(command[x], 1);
				x++;
			}
		}
		if (arg->next)
			ft_putchar_fd(' ', 1);
		arg = arg->next;
	}
}

int	builtin_echo(t_list *arg)
{
	int		new_line;
	int		i;
	t_list	*tmp;

	new_line = 1;
	i = 1;
	tmp = arg;
	if (!arg->next)
	{
		printf("\n");
		return (0);
	}
	while (tmp->next && ft_strcmp((char *)(tmp->next->content), "-n") == 0)
	{
		new_line = 0;
		i++;
		tmp = tmp->next;
	}
	write_echo(arg, i);
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
