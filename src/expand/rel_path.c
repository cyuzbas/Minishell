/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rel_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatstra <mbatstra@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:27:40 by mbatstra          #+#    #+#             */
/*   Updated: 2022/09/21 17:08:28 by mbatstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

// it doesn't do .. (parent dir), not sure if it should tho
// because it's not in the subject but also it's a file rather than
// a special character right?
//
// probably better to do tile expansion in a separate func?
// 
// ft_strlcat uses len + 1 because null byte is already there
char	*expand_relpath(char *relp)
{
	char	*abs_path;
	char	*pwd;
	int		abs_len;

	pwd = NULL;
	pwd = getcwd(pwd, 1);
	if (pwd == NULL)
		return (NULL);
	abs_len = ft_strlen(relp) + ft_strlen(pwd) + 1;
	abs_path = (char *)ft_calloc(abs_len + 1, sizeof(char));
	ft_strlcpy(abs_path, pwd, abs_len);
	abs_path[ft_strlen(pwd)] = '/';
	ft_strlcat(abs_path, relp, abs_len + 1);
	return (abs_path);
}
