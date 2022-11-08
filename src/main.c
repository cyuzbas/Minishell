/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 17:37:17 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/07 13:05:52 by mbatstra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"
#include "exec.h"

static void	change_shlvl(t_list **envp)
{
	int		shlvl;
	char	*level;
	char	*minipwd;

	shlvl = ft_atoi(env_getval(*envp, "SHLVL", 5));
	shlvl += 1;
	level = protect_itoa(shlvl);
	env_setval(envp, "SHLVL", level);
	minipwd = env_getval(*envp, "PWD", 3);
	minipwd = ft_strjoin(minipwd, "/minishell");
	env_setval(envp, "SHELL", minipwd);
	free(level);
	free(minipwd);
}

static void	ft_exit(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

static void	parse_exec(char *input, t_list **tokens, t_list *new_env)
{
	t_simplecmd	**cmd_table;

	add_history(input);
	cmd_table = parse_cmd_init(*tokens);
	g_exit_code = parse_tokens(cmd_table, &tokens, new_env);
	execute(cmd_table, &new_env);
	parse_clear_cmd_table(cmd_table);
}

static void	minishell(t_list *new_env)
{
	t_list	*tokens;
	char	*input;
	int		lex_exit;

	input = readline("minishell-$ ");
	if (input == NULL)
		ft_exit();
	tokens = NULL;
	lex_exit = lexer_tokenize(&tokens, input);
	if (lex_exit)
	{
		add_history(input);
		g_exit_code = lex_exit;
	}
	else if (ft_strlen(input))
		parse_exec(input, &tokens, new_env);
	ft_lstclear(&tokens, &lexer_clear_token);
	if (g_exit_code == 12)
		ft_putendl_fd("Allocation failure", 2);
	free(input);
}

int	main(int argc, char **argv, char **env)
{
	t_list	*new_env;

	(void)argv;
	if (argc == 1)
	{
		g_exit_code = 0;
		signal_suppress_output();
		new_env = NULL;
		env_init(env, &new_env);
		change_shlvl(&new_env);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &catch_int);
		while (1)
		{
			signal(SIGINT, &catch_int);
			signal(SIGQUIT, SIG_IGN);
			minishell(new_env);
		}
	}
	return (0);
}
