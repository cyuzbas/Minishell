/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/11/04 17:49:49 by mbatstra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

void	middle_command(t_simplecmd *cmds, t_list **env, int fd[2], int fd_end)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		exit(-1);
	else if (pid == 0)
	{
		signal(SIGINT, catch_int_child);
		signal(SIGQUIT, catch_quit);
		protect_dup2(fd[1], STDOUT_FILENO);
		protect_dup2(fd_end, STDIN_FILENO);
		protect_close(fd[0]);
		protect_close(fd[1]);
		protect_close(fd_end);
		choose_execute(cmds, env);
		exit(g_mini.exit_code);
	}
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, catch_quit_parent);
	}
}

void	last_command(t_simplecmd *cmds, t_list **env, int fd[2], int *lastid)
{
	*lastid = fork();
	if (*lastid == -1)
		exit(-1);
	else if (*lastid == 0)
	{
		signal(SIGINT, catch_int_child);
		signal(SIGQUIT, catch_quit);
		protect_dup2(fd[0], STDIN_FILENO);
		protect_close(fd[0]);
		choose_execute(cmds, env);
		exit(g_mini.exit_code);
	}
	if (*lastid > 0)
	{
		signal(SIGINT, catch_int_child);
		signal(SIGQUIT, catch_quit_parent);
	}
}

void	first_command(t_simplecmd *cmds, t_list **env, int fd[2])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(-1);
	else if (pid == 0)
	{
		signal(SIGINT, catch_int_child);
		signal(SIGQUIT, catch_quit);
		protect_close(fd[0]);
		protect_dup2(fd[1], STDOUT_FILENO);
		protect_close(fd[1]);
		choose_execute(cmds, env);
		exit(g_mini.exit_code);
	}
	if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, catch_quit_parent);
	}
}

void	single_command(t_simplecmd *cmds, t_list **env, int *lastpid)
{
	*lastpid = fork();
	if (*lastpid == -1)
		exit(-1);
	if (*lastpid == 0)
	{
		signal(SIGINT, catch_int_child);
		signal(SIGQUIT, catch_quit);
		choose_execute(cmds, env);
		exit(g_mini.exit_code);
	}
	if (*lastpid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, catch_quit_parent);
	}
}

void	ft_fork(int i, t_simplecmd **cmds, t_list **env, t_fd *fd)
{
	if (i == 0 && !cmds[i + 1])
		single_command(cmds[i], env, fd->last_pid);
	else if (i == 0)
		first_command(cmds[i], env, fd->fdpipe);
	else if (!cmds[i + 1])
		last_command(cmds[i], env, fd->fdpipe, fd->last_pid);
	else
		middle_command(cmds[i], env, fd->fdpipe, fd->fd_end);
}
