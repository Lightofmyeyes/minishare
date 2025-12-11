/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:04:40 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/10 15:08:44 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "libft/libft.h"

char	*get_env_var(char *name, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	set_env_var(char *name, char *value, char ***envp)
{
	int	i;
	int	len;
	char	*new_var;
	char	*temp;
	char	**new_envp;

	i = 0;
	len = ft_strlen(name);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			temp = ft_strjoin(name, "=");
			if (!temp)
				return (-1);
			new_var = ft_strjoin(temp, value);
			free(temp);
			if (!new_var)
				return (-1);
			(*envp)[i] = new_var;
			return (0);
		}
		i++;
	}
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (-1);
	new_var = ft_strjoin(temp, value);
	free(temp);
	if (!new_var)
		return (-1);
	i = 0;
	while ((*envp)[i])
		i++;
	new_envp = ft_realloc(*envp, i, i + 2);
	if (!new_envp)
	{
		free(new_var);
		return (-1);
	}
	*envp = new_envp;
	(*envp)[i] = new_var;
	(*envp)[i + 1] = NULL;
	return (0);
}

char *expand_tilde(char *path, char **envp)
{
	char *home;
	char *new_path;

	home = get_env_var("HOME", envp);
	if (!home)
		return (ft_strdup(path));
	new_path = ft_strjoin(home, path + 1);
	return (new_path);
}

int	unset_env_var(char *name, char ***envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			while ((*envp)[i + 1])
			{
				(*envp)[i] = (*envp)[i + 1];
				i++;
			}
			(*envp)[i] = NULL;
			return (0);
		}
		i++;
	}
	return (-1);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char **ft_realloc(char **src, int old_size, int new_size)
{
	char **new;
	int	i;

	new = malloc(sizeof(char *) * (new_size));
	if (!new)
		return (NULL);
	i = 0;
	while (i < old_size && src[i])
	{
		new[i] = src[i];
		i++;
	}
	while (i < new_size)
	{
		new[i] = NULL;
		i++;
	}
	free(src);
	return (new);
}
