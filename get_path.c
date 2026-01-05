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
//static char	*find_next_dir(char *current_dir);

char	*get_path(char **cmds, t_list *env_list)
{
	char	*path_env;
	char	*result;
	char	**envp;
	int	i;

//	printf("DEBUG: get_path called for command '%s'\n", cmds[0] ? cmds[0] : "(null)");
	if (!cmds || !cmds[0])
	{
//		printf("DEBUG: Invalid command\n");
		return (NULL);
	}
	envp = convert_env_list_to_envp(env_list);
	if (!envp)
	{
//		printf("DEBUG: Failed to convert env_list to envp\n");
		return (NULL);
	}
//	printf("DEBUG: Environment variables:\n");
	i = 0;
	while (envp[i])
	{
//		printf("DEBIG: %s\n", envp[i]);
		i++;
	}
	if (strchr(cmds[0], '/'))
	{
//		printf("DEBUG: Command contrains '/', treating as path %s\n", cmds[0]);
		if (access(cmds[0], X_OK) == 0)
		{
//			printf("DEBUG: Path is valid and executable\n");
			result = ft_strdup(cmds[0]);
			free_envp(envp);
			return (result);
		}
		else
		{
			printf("DEBUG: Path exists but i not executable or doesnt exist\n");
		}
		free_envp(envp);
		return (NULL);
	}
	path_env = get_path_env(envp);
	if (!path_env)
	{
//		printf("DEBUG: PATH not found in environment\n");
		free_envp(envp);
		return (NULL);
	}
//	printf("DEBUG: PATH = %s\n", path_env);
	result = find_in_path(cmds[0], path_env);
	if (result)
		printf("DEBUG: Found command at: %s\n", result);
	else
		printf("DEBUG: Command not found in path\n");
	free_envp(envp);
	return (result);
}

/*			
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
*/

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
		printf("DEBUG: tentando diretório: '%s'\n", dirs[i]);
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

/*
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
*/

/*
static char *find_next_dir(char *current_dir)
{
	while (*current_dir && *current_dir != ':')
		current_dir++;
	if (*current_dir == ':')
		return (current_dir + 1);
	return (NULL);
}
*/
