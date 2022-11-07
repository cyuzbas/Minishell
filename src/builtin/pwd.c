/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:15:35 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/21 16:33:16 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	builtin_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 1);
	if (path == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}
