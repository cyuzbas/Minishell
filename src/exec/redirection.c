/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/11/04 16:46:47 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	set_infile(t_simplecmd *cmds)
{
	t_token	*rdr_in;
	t_list	*in;
	int		id;

	in = *(cmds->in);
	while (in)
	{
		rdr_in = in->content;
		if (rdr_in->type == RDR_IN || rdr_in->type == HEREDOC)
		{
			id = open(rdr_in->value, O_RDONLY);
			if (id < 0)
			{
				print_error(rdr_in->value, NULL, NULL);
				g_mini.exit_code = 1;
				exit(1);
			}
			protect_dup2(id, STDIN_FILENO);
			protect_close(id);
			if (rdr_in->type == HEREDOC)
				unlink(rdr_in->value);
		}
		in = in->next;
	}
}

void	set_outfile(t_simplecmd *cmds)
{
	t_token	*rdr_out;
	t_list	*out;
	int		fd;

	out = *(cmds->out);
	while (out)
	{
		rdr_out = out->content;
		if (rdr_out->type == RDR_OUT || rdr_out->type == RDR_APP)
		{
			if (rdr_out->type == RDR_OUT)
				fd = open(rdr_out->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else
				fd = open(rdr_out->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd < 0)
			{
				print_error(rdr_out->value, NULL, NULL);
				g_mini.exit_code = 1;
				exit(1);
			}
			protect_dup2(fd, STDOUT_FILENO);
			protect_close(fd);
		}
		out = out->next;
	}
}
