/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:21 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/11/04 16:19:50 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# include "minishell.h"

# define TRUE 1
# define FALSE 0

typedef struct s_mini
{
	int	exit_code;
	int	interactive;
}			t_mini;

t_mini	g_mini;

typedef struct s_fd
{
	int			fdpipe[2];
	int			fd_end;
	int			*last_pid;
}				t_fd;

char	**envp_array(t_list *env_lst);

//execution
void	execute(t_simplecmd **cmds, t_list **envp);
void	ft_fork(int i, t_simplecmd **cmds, t_list **env, t_fd *fd);
int		wait_children(int last_process_pid);
void	error_exit(int exit_code, char *cmd, char *message);
void	print_error(char *command, char *arg, char *text);

void	ft_execve(t_simplecmd *simplecmd, t_list **envp);

//redirection
int		heredoc(t_simplecmd **cmds, t_list **envp);
void	set_infile(t_simplecmd *cmds);
void	set_outfile(t_simplecmd *cmds);

//execute functions for builtin
int		builtin_and_redirection(t_simplecmd **cmds);
void	execute_builtin(t_simplecmd *cmds, t_list **env);
int		is_builtin(t_simplecmd *cmds);
void	choose_execute(t_simplecmd *cmds, t_list **env);
int		ft_strcmp(const char *s1, const char *s2);

//simple functions with malloc protection
char	*protect_itoa(int i);
char	*strdup_protect(char *s1);
char	*join_protect(char *s1, char *s2);
void	protect_close(int id);
void	protect_dup2(int fd, int i);

//export_utils
void	free_spl_nameval(char **spl_nameval);
int		write_export_env(t_list *envp);
#endif