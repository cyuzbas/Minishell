/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/11/04 11:24:01 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

static void	set_heredoc(t_simplecmd **cmds)
{
	size_t	i;
	size_t	j;
	t_list	*in;
	char	*a;

	i = 0;
	j = 0;
	while (cmds[j])
	{
		in = *(cmds[j]->in);
		while (in)
		{
			if (((t_token *)in->content)->type == HEREDOC)
			{
				a = protect_itoa(i);
				free(((t_token *)in->content)->value);
				((t_token *)in->content)->value = join_protect("/tmp/hdoc_", a);
				free(a);
				i++;
			}
			in = in->next;
		}
		j++;
	}
}

static void	write_to_heredoc(t_list *lst, t_token *redirection, t_list **envp)
{
	int		fd;
	char	new_line;

	new_line = '\n';
	fd = open(redirection->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		print_error(redirection->value, NULL, NULL);
		exit(1);
	}
	while (lst)
	{
		if (ft_strrchr(lst->content, '$'))
			lst->content = parse_expand_env(lst->content, *envp);
		if (!lst->content)
			exit (1);
		write(fd, lst->content, ft_strlen(lst->content));
		write(fd, &new_line, sizeof(new_line));
		lst = lst->next;
	}
	close(fd);
	ft_lstclear(&lst, free);
}

static void	handle_heredoc(t_token *redirection, char *eof, t_list **envp)
{
	t_list	*here_doc_input_list;
	char	*read_txt;

	here_doc_input_list = NULL;
	while (1)
	{
		read_txt = readline("> ");
		if (read_txt == NULL)
			break ;
		else if (ft_strcmp(eof, read_txt) == 0)
		{
			free(read_txt);
			break ;
		}
		ft_lstadd_back(&here_doc_input_list, ft_lstnew(read_txt));
	}
	free(eof);
	write_to_heredoc(here_doc_input_list, redirection, envp);
}

static void	child_heredoc(t_simplecmd **cmds, t_list **envp)
{
	size_t	i;
	int		j;
	char	*delim;
	t_list	*in;

	i = 0;
	j = 0;
	while (cmds[j])
	{
		in = *(cmds[j]->in);
		while (in)
		{
			if (((t_token *)in->content)->type == HEREDOC)
			{
				delim = strdup_protect(((t_token *)in->content)->value);
				((t_token *)in->content)->value = join_protect("/tmp/hdoc_", \
				protect_itoa(i));
				handle_heredoc(((t_token *)in->content), delim, envp);
				i++;
			}
			in = in->next;
		}
		j++;
	}
	exit (0);
}

int	heredoc(t_simplecmd **cmds, t_list **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit (-1);
	if (pid == 0)
	{
		signal(SIGINT, catch_int_hrdc);
		child_heredoc(cmds, envp);
	}
	if (pid > 0)
	{
		signal(SIGINT, catch_parent_hrdc);
		signal(SIGQUIT, SIG_IGN);
	}
	g_mini.exit_code = wait_children(pid);
	set_heredoc(cmds);
	return (TRUE);
}
