/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sigint.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 11:59:24 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/07 12:43:15 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <signal.h>
#include "minishell.h"
#include "exec.h"

void	catch_int(int sig)
{
	g_exit_code = 1;
	signal(sig, &catch_int);
	ioctl(IN, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	catch_int_child(int sig)
{
	g_exit_code = 1;
	signal(sig, &catch_int_child);
}

void	catch_int_hrdc(int sig)
{
	(void)sig;
	g_exit_code = 1;
	printf("\n");
	exit(EXIT_FAILURE);
}

void	catch_parent_hrdc(int sig)
{
	g_exit_code = 1;
	signal(sig, &catch_parent_hrdc);
}
