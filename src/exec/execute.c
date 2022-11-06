/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/11/04 17:57:20 by mbatstra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

void	exec_pipe(t_simplecmd **cmds, t_list **env, int *last_pid)
{
	t_fd	fd;
	int		idx;

	idx = 0;
	fd.fd_end = -1;
	fd.last_pid = last_pid;
	while (cmds[idx] != NULL)
	{
		if (cmds[idx + 1] != NULL)
			if (pipe(fd.fdpipe) == -1)
				exit(1);
		ft_fork(idx, cmds, env, &fd);
		if (fd.fd_end != -1)
		{
			protect_close(fd.fd_end);
			if (cmds[idx + 1] != NULL)
				fd.fd_end = fd.fdpipe[0];
		}
		else
			fd.fd_end = fd.fdpipe[0];
		idx++;
		if (cmds[idx] != NULL)
			protect_close(fd.fdpipe[1]);
	}
}

void	execute2(t_simplecmd **cmds, t_list **envp)
{
	int		last_pid;
	t_list	*in;
	t_list	*out;
	t_list	*arg;

	arg = *(*cmds)->arg;
	in = *(*cmds)->in;
	out = *(*cmds)->out;
	last_pid = 0;
	exec_pipe(cmds, envp, &last_pid);
	g_mini.exit_code = wait_children(last_pid);
	if (arg && g_mini.exit_code == 0 \
		&& (ft_strcmp((char *)(arg->content), "cd") == 0 \
		|| ft_strcmp((char *)(arg->content), "unset") == 0))
		execute_builtin(*cmds, envp, 0);
	else if (arg && g_mini.exit_code == 0 && in \
	&& ft_strcmp((char *)(arg->content), "exit") == 0)
		builtin_exit(arg, &g_mini.exit_code, 0);
	else if (arg && out \
	&& ft_strcmp((char *)(arg->content), "exit") == 0)
		exit(g_mini.exit_code);
}

void	execute(t_simplecmd **cmds, t_list **envp)
{
	if (!heredoc(cmds, envp))
	{
		g_mini.exit_code = -1;
		return ;
	}
	if (g_mini.interactive != 0)
	{
		if (builtin_and_redirection(cmds) || !is_builtin(*cmds))
			execute2(cmds, envp);
		else
			execute_builtin(*cmds, envp, 0);
	}
}
