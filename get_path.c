/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 00:00:00 by fpedroso          #+#    #+#             */
/*   Updated: 2026/01/05 16:18:05 by lcosta-a         ###   ########.fr       */
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
//	int	i;

	printf("DEBUG: get_path - cmd[0] = %s\n", cmds[0]);
	if (!cmds || !cmds[0])
	{
		printf("DEBUG: cmds ou cmds[0] é NULL!\n");
		return (NULL);
	}
	envp = convert_env_list_to_envp(env_list);
	if (!envp)
	{
		printf("DEBUG: envp é NULL\n");
		return (NULL);
	}
//	i = 0;
	if (strchr(cmds[0], '/'))
	{
		if (access(cmds[0], X_OK) == 0)
		{
			result = ft_strdup(cmds[0]);
			free_envp(envp);
			printf("DEBUG: Caminho absoluto não entrado %s\n", result);
			return (result);
		}
		free_envp(envp);
		printf("DEBUG: Caminho absoluto não encontrado\n");
		return (NULL);
	}
	path_env = get_path_env(envp);
	if (!path_env)
	{
		printf("DEBUG: Path não encontrado no environment\n");
		free_envp(envp);
		return (NULL);
	}
	result = find_in_path(cmds[0], path_env);
	free_envp(envp);
	if (result)
		printf("DEBUG: Comando encontrado em %s\n", result);
	else
		printf("DEBUG: Comando NÃO ENCONTRADO NO PATH\n");
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
	int		i;
	char	**dirs;
	char	*full_path;
	
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		full_path = join_path(dirs[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			ft_free_split(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

static char *join_path(char *dir, char *cmd)
{
	size_t	dir_len;
	size_t	cmd_len;
	size_t	total_len;
	char	*result;
	char	*p;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	total_len = dir_len + cmd_len + 2;
	result = malloc(total_len);
	if (!result)
		return (NULL);
	p = result;
	ft_memcpy(p, dir, dir_len);
	p += dir_len;
	if (dir_len > 0 && dir[dir_len - 1] != '/')
	{
		*p = '/';
		p++;
	}
	ft_memcpy(p, cmd, cmd_len);
	p += cmd_len;
	*p = '\0';
	return (result);
}
