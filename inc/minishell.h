/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbatstra <mbatstra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 17:37:27 by mbatstra      #+#    #+#                 */
/*   Updated: 2022/11/04 16:36:53 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define IN 0
# define OUT 1
# define ERR 2

# include "libft.h"

enum e_types {
	RDR_IN,
	HEREDOC,
	RDR_OUT,
	RDR_APP,
	PIPE,
	WORD
};

typedef struct s_token {
	enum e_types	type;
	char			*value;
	int				expand;
}			t_token;

typedef struct s_lexer_flags {
	int	is_single_quoted;
	int	is_double_quoted;
	int	is_delim;
	int	last_exit;
}			t_lexer_flags;

typedef struct s_simplecmd {
	t_list	**arg;
	t_list	**in;
	t_list	**out;
}			t_simplecmd;

// lexing 
t_token		*lexer_token_copy(t_token *token);
void		lexer_clear_token(void *token);
void		lexer_token_identifier(t_token *token);
void		lexer_tokenize_word(t_token *token, char *cmd, \
								int *i, t_lexer_flags *flags);
void		lexer_tokenize_operator(t_token *token, char *cmd, \
									int *i, t_lexer_flags *flags);
int			lexer_tokenize(t_list **tokens, char *cmd_line);
int			lexer_value_append(t_token *token, char *value, int val_len);
int			lexer_is_operator_char(char c);
int			lexer_error(t_list *tokens);

// parsing
t_simplecmd	**parse_cmd_init(t_list *tokens);
char		*parse_expand_env(char *old_val, t_list *envp);
void		parse_clear_cmd_table(t_simplecmd **cmd_table);
int			parse_tokens(t_simplecmd **cmd, t_list **tokens, t_list *envp);
int			parse_redir(t_simplecmd **cmd_table, t_list **tokens);
int			parse_word(t_simplecmd **cmd_table, t_list **tokens);
int			parse_expand(t_list *tokens, t_list *env);

// expansion
char		*has_expansion(char *str);
char		*expand_relpath(char *relp);
char		*expand_parent_dir(t_list *envp);

// functions for expandign and setting env vars
void		env_init(char **envp, t_list **new_env);
void		env_setval(t_list **envp, const char *name, const char *val);
char		*env_getval(t_list *envp, const char *name, int namelen);

// builtins
void		builtin_exit(t_list *arg, int *exit_code);
int			builtin_export(t_list **envp, t_list *arg);
int			builtin_unset(t_list **envp, t_list *arg);
int			builtin_cd(char *path, t_list **envp);
int			builtin_pwd(void);
int			builtin_echo(t_list *arg);
int			builtin_env(t_list *envp);

// signals
void		signal_suppress_output(void);
void		catch_quit(int sig);
void		catch_int(int sig);
void		catch_int_child(int sig);
void		catch_int_hrdc(int sig);
void		catch_parent_hrdc(int sig);
void		catch_quit_parent(int sig);
void		signal_parent(void);

#endif 
