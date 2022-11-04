/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/11/03 17:09:16 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

int	is_builtin(t_simplecmd *cmds)
{
	t_list	*arg;
	int		is_builtin;

	arg = *(cmds->arg);
	is_builtin = FALSE;
	if (arg != NULL)
	{
		if (ft_strcmp((char *)(arg->content), "cd") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "pwd") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "exit") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "echo") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "env") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "export") == 0)
			is_builtin = TRUE;
		else if (ft_strcmp((char *)(arg->content), "unset") == 0)
			is_builtin = TRUE;
	}
	return (is_builtin);
}

void	execute_builtin(t_simplecmd *cmds, t_list **env)
{
	t_list	*arg;
	char	*command_next;

	arg = *(cmds->arg);
	if (!arg->next)
		command_next = NULL;
	else
		command_next = (char *)(arg->next->content);
	if (ft_strcmp((char *)(arg->content), "cd") == 0)
		g_mini.exit_code = builtin_cd(command_next, env);
	else if (ft_strcmp((char *)(arg->content), "pwd") == 0)
		g_mini.exit_code = builtin_pwd();
	else if (ft_strcmp((char *)(arg->content), "exit") == 0)
		builtin_exit(arg, &g_mini.exit_code);
	else if (ft_strcmp((char *)(arg->content), "echo") == 0)
		g_mini.exit_code = builtin_echo(arg);
	else if (ft_strcmp((char *)(arg->content), "env") == 0)
		g_mini.exit_code = builtin_env(*env);
	else if (ft_strcmp((char *)(arg->content), "export") == 0)
		g_mini.exit_code = builtin_export(env, arg);
	else if (ft_strcmp((char *)(arg->content), "unset") == 0)
		g_mini.exit_code = builtin_unset(env, arg);
}

int	builtin_and_redirection(t_simplecmd **cmds)
{
	t_list	*in;
	t_list	*out;

	in = *(cmds[0]->in);
	out = *(cmds[0]->out);
	if ((in || out || cmds[1]) && is_builtin(cmds[0]))
		return (1);
	return (0);
}
