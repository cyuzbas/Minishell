/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cyuzbas <cyuzbas@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/29 10:26:25 by cyuzbas       #+#    #+#                 */
/*   Updated: 2022/10/18 18:37:09 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/exec.h"

char	*join_protect(char *s1, char *s2)
{
	char	*s3;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s3 = ft_strjoin(s1, s2);
	if (!s3)
	{
		perror("Malloc failed");
		exit (-1);
	}
	return (s3);
}

char	*strdup_protect(char *s1)
{
	char	*s2;

	if (s1 == NULL)
		return (NULL);
	s2 = ft_strdup(s1);
	if (!s2)
	{
		perror("Malloc failed");
		exit (-1);
	}
	return (s2);
}

char	*protect_itoa(int i)
{
	char	*txt;

	txt = ft_itoa(i);
	if (!txt)
		exit(1);
	return (txt);
}

void	protect_dup2(int fd, int i)
{
	int	result;

	result = dup2(fd, i);
	if (result == -1)
	{
		perror("dup2 error");
		exit(1);
	}
}

void	protect_close(int id)
{
	int	result;

	result = close(id);
	if (result == -1)
		exit(1);
}
