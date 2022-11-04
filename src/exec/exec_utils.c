/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/11/04 16:19:28 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

void	error_exit(int exit_code, char *cmd, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd != NULL)
		ft_putstr_fd(cmd, 2);
	if (message == NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		if (errno == ENOTDIR || errno == EACCES)
			exit (126);
	}
	else
		ft_putstr_fd(message, 2);
	exit(exit_code);
}

void	print_error(char *command, char *arg, char *text)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	if (arg != NULL)
		ft_putstr_fd(arg, 2);
	if (text == NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
	}
	else
		ft_putstr_fd(text, 2);
	ft_putstr_fd("\n", 2);
}

int	wait_children(int last_process_pid)
{
	int	pid;
	int	last_process_exit_status;
	int	status;

	pid = 1;
	last_process_exit_status = 0;
	while (pid > 0)
	{
		pid = wait(&status);
		if (pid == last_process_pid)
		{
			if (WIFEXITED(status))
				last_process_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_process_exit_status = WTERMSIG(status) + 128;
		}
	}
	return (last_process_exit_status);
}

void	choose_execute(t_simplecmd *cmds, t_list **env)
{
	t_list	*in;
	t_list	*out;
	t_list	*arg;

	in = *(cmds->in);
	out = *(cmds->out);
	arg = *(cmds->arg);
	if (in)
		set_infile(cmds);
	if (out)
		set_outfile(cmds);
	if (arg)
	{	
		if (is_builtin(cmds))
			execute_builtin(cmds, env);
		else
			ft_execve(cmds, env);
	}
}
