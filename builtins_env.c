/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:16:37 by lcosta-a          #+#    #+#             */
/*   Updated: 2026/01/04 00:54:22 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include "libft/libft.h"
#include <limits.h>
#include <unistd.h>
#include "env_utils.h"

int	ft_cd(t_token *tokens, char ***envp)
{
	char	*path;
	char	*oldpwd;
	char	cwd[PATH_MAX];
	int		should_free_path;

	should_free_path = 0;
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	if (!tokens->next || !tokens->next->value || tokens->next->value[0] == '\0')
		path = get_env_var("HOME", *envp);
	else if (tokens->next->value[0] == '~')
	{
		path = expand_tilde(tokens->next->value, *envp);
		should_free_path = 1;
	}
	else if (tokens->next->value[0] == '-' && tokens->next->value[1] == '\0')
		path = get_env_var("OLDPWD", *envp);
	else
		path = tokens->next->value;
	if (!path || chdir(path) == -1)
	{
		if (should_free_path)
			free(path);
		free(oldpwd);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		if (should_free_path)
			free (path);
		free(oldpwd);
		return (1);
	}
	set_env_var("OLDPWD", oldpwd, envp);
	set_env_var("PWD", cwd, envp);
	if (should_free_path)
		free(path);
	free(oldpwd);
	return (0);
}

int	ft_export(t_token *tokens, char ***envp)
{
	char	*value;
	char	*name;
	char	*equal_sign;

	if (!tokens->next)
	{
		ft_env(*envp);
		return (0);
	}
	while (tokens->next && tokens->next->type == WORD)
	{
		equal_sign = ft_strchr(tokens->next->value, '=');
		if (!equal_sign)
		{
			if (!get_env_var(tokens->next->value, *envp))
				return (1);
		}
		else
		{
			name = ft_substr(tokens->next->value, 0, equal_sign - tokens->next->value);
			value = equal_sign + 1;
			if (set_env_var(name, value, envp) == -1)
			{
				free(name);
				return (1);
			}
			free(name);
		}
		tokens = tokens->next;
	}
	return (0);
}

int	ft_unset(t_token *tokens, char ***envp)
{
	int	i;

	i = 1;
	if (!tokens->next)
		return (1);
	while (tokens->next && tokens->next->type == WORD)
	{
		if (unset_env_var(tokens->next->value, envp) == -1)
			return (1);
		tokens = tokens->next;
		i++;
	}
	return (0);
}

int ft_exit(char **args, int *exit_status)
{
	int	status;

	status = 0;
	if (args[1])
	{
		if (args[2])
		{
			ft_putstr("exit: too manu arguments\n");
			return (1);
		}
		if (!is_numeric(args[1]))
		{
			ft_putstr("exit: numeric argument required\n");
			status = 2;
			*exit_status = status;
			return (status);
		}
		status = ft_atoi(args[1]);
	}
	*exit_status = status;
	return (-2);
}
