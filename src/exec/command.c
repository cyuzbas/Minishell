/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cicekyuzbas <cyuzbas@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/03 21:36:18 by cicekyuzbas   #+#    #+#                 */
/*   Updated: 2022/11/03 12:58:45 by cyuzbas       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

static void	ft_free(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*join_path(char **paths, char *cmd)
{
	char	*full_path;
	char	*tmp_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	ft_free(paths);
	return (NULL);
}

static char	*find_path(char *cmd, t_list **envp)
{
	char	**paths;
	char	*full_path;
	char	*path;

	path = NULL;
	path = env_getval(*envp, "PATH", 4);
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	full_path = join_path(paths, cmd);
	if (full_path)
		return (full_path);
	free(full_path);
	return (0);
}

char	**change_if_expanded(char **cmd_arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd_arr[0][i])
	{
		if (cmd_arr[0][i] != ' ' && \
		(cmd_arr[0][i + 1] == ' ' || !cmd_arr[0][i + 1]))
			count++;
		i++;
	}
	if (count > 1)
		cmd_arr = ft_split(cmd_arr[0], ' ');
	if (!cmd_arr)
		exit(-1);
	return (cmd_arr);
}

void	ft_execve(t_simplecmd *simplecmd, t_list **envp)
{
	char	*path;
	char	**envp_arr;
	char	**cmd_arr;

	cmd_arr = envp_array(*(simplecmd->arg));
	cmd_arr = change_if_expanded(cmd_arr);
	envp_arr = envp_array(*envp);
	if (ft_strchr(cmd_arr[0], '/') != 0)
	{
		execve(cmd_arr[0], cmd_arr, envp_arr);
		if (errno == ENOENT)
			error_exit(127, cmd_arr[0], ": No such file or directory\n");
		else
			error_exit(1, cmd_arr[0], NULL);
	}
	else if (envp[0])
	{
		path = find_path(cmd_arr[0], envp);
		execve(path, cmd_arr, envp_arr);
		error_exit(127, cmd_arr[0], ": command not found\n");
	}
}
