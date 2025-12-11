/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:05:59 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/10 18:59:34 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft/libft.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd, "env"))
		return (ENV);
	if (!ft_strcmp(cmd, "cd"))
		return (CD);
	if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (NOT_BUILTIN);
}

int	execute_builtin(t_token *tokens, char ***envp, int *exit_status)
{
	(void)envp;
	if (!tokens)
		return (-1);
	if (is_builtin(tokens->value) != NOT_BUILTIN)
	{
		if (is_builtin(tokens->value) == ECHO)
			return (ft_echo(tokens));
		else if (is_builtin(tokens->value) == PWD)
			return (ft_pwd());
		else if (is_builtin(tokens->value) == ENV)
			return (ft_env(*envp));
		else if (is_builtin(tokens->value) == CD)
			return (ft_cd(tokens, envp));
		else if (is_builtin(tokens->value) == EXPORT)
			return (ft_export(tokens, envp));
		else if (is_builtin(tokens->value) == UNSET)
			return (ft_unset(tokens, envp));
		else if (is_builtin(tokens->value) == EXIT)
			return (ft_exit(tokens, exit_status));
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
