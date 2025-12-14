/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:00:00 by fpedroso          #+#    #+#             */
/*   Updated: 2025/12/01 18:17:05 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "get_path.h"
#include "env_utils.h"
#include "builtins.h"
#include <limits.h>
#include <unistd.h>

static char	*find_in_path(char *cmd, char *path_env);
static char	*get_path_env(char **envp);
static char	*join_path(char *dir, char *cmd);

char	*get_path(char **cmds, t_list *env_list)
{
	char	*path_env;
	char	*result;
	char	**envp;

	if (!cmds || !cmds[0])
		return (NULL);
	envp = convert_env_list_to_envp(env_list);
	if (!envp)
		return (NULL);
	if (strchr(cmds[0], '/'))
	{
		if (access(cmds[0], X_OK) == 0)
		{
			result = ft_strdup(cmds[0]);
			return (result);
		}
		free_envp(envp);
		return (NULL);
	}
	path_env = get_path_env(envp);
	if (!path_env)
	{
		free_envp(envp);
		return (NULL);
	}
	result = find_in_path(cmds[0], path_env);
	free_envp(envp);
	return (result);
}

static char	*get_path_env(char **envp)
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*find_in_path(char *cmd, char *path_env)
{
	char	*path_copy;
	char	*dir;
	char	*full_path;
	char	*saveptr;

	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	dir = strtok_r(path_copy, ":", &saveptr);
	while (dir)
	{
		full_path = join_path(dir, cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok_r(NULL, ":", &saveptr);
	}
	free(path_copy);
	return (NULL);
}

static char	*join_path(char *dir, char *cmd)
{
	char	*result;
	size_t	len;

	if (!dir || !cmd)
		return (NULL);
	
	len = strlen(dir) + strlen(cmd) + 2; // +2 for '/' and '\0'
	result = (char *)malloc(len);
	if (!result)
		return (NULL);
	
	strcpy(result, dir);
	if (dir[strlen(dir) - 1] != '/')
		strcat(result, "/");
	strcat(result, cmd);
	
	return (result);
}
