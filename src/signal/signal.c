/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 17:42:50 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/04 16:37:15 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "readline/readline.h"
#include "readline/history.h"
#include "minishell.h"
#include "libft.h"
#include "exec.h"

void	signal_suppress_output(void)
{
	struct termios	s_termios;

	if (tcgetattr(0, &s_termios))
		perror("minishell: tcsetattr");
	s_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &s_termios))
		perror("minishell: tcsetattr");
}

// only for running child-process
void	catch_quit(int sig)
{
	signal(sig, &catch_quit);
	g_mini.exit_code = 131;
	exit(g_mini.exit_code);
}

void	catch_quit_parent(int sig)
{
	ft_putstr_fd("Quit: 3\n", 2);
	g_mini.exit_code = 131;
	signal(sig, &catch_parent_hrdc);
}

void	signal_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, catch_quit_parent);
}
