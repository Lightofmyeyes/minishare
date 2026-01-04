/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:05:59 by lcosta-a          #+#    #+#             */
/*   Updated: 2026/01/04 06:30:31 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"
#include "utils.h"
#include <unistd.h>

int	is_builtin(char *cmd)
{
	return (cmd && (
		!ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "pwd") ||
		!ft_strcmp(cmd, "export") ||
		!ft_strcmp(cmd, "unset") ||
		!ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "exit")
		));

}

int	execute_builtin(t_token *tokens, char ***envp, int *exit_status)
{
	char	**args;
	int		result;
	(void)envp;

	args = NULL;
	if (!tokens || !is_builtin(tokens->value))
		return (-1);
	if (is_builtin(tokens->value))
	{
		if (!ft_strcmp(tokens->value, "echo"))
			return (ft_echo(tokens));
		if (!ft_strcmp(tokens->value, "pwd"))
			return (ft_pwd());
		if (!ft_strcmp(tokens->value, "env"))
			return (ft_env(*envp));
		if (!ft_strcmp(tokens->value, "cd"))
			return (ft_cd(tokens, envp));
		if (!ft_strcmp(tokens->value, "export"))
			return (ft_export(tokens, envp));
		if (!ft_strcmp (tokens->value, "unset"))
			return (ft_unset(tokens, envp));
		if (!ft_strcmp (tokens->value, "exit"))
		{
			args = tokens_to_args(tokens);
			result = ft_exit(args, exit_status);
			free_args(args);
			return result;
		}
	}
	return (-1);
}

int	ft_echo(t_token *tokens)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (tokens->next && !ft_strcmp(tokens->next->value, "-n"))
	{
		newline = 0;
		i = 2;
	}
	while (tokens->next && i > 0 && tokens->next->type == WORD)
	{
		ft_putstr(tokens->next->value);
		tokens = tokens->next;
		if (tokens->next && tokens->next->type == WORD)
			ft_putchar(' ');
	}
	if (newline)
		ft_putchar('\n');
	return (0);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if(!cwd)
		return (1);
	ft_putstr(cwd);
	ft_putchar('\n');
	free(cwd);
	return (0);
}

int	ft_env(char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i])
	{
		ft_putstr(envp[i]);
		ft_putchar('\n');
		i++;
	}
	return (0);
}
