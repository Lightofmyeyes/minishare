/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_adapter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:31:27 by lcosta-a          #+#    #+#             */
/*   Updated: 2026/01/04 06:53:00 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "minishell.h"
#include "ast_converter.h"
#include "libft/libft.h"

int adapter_echo(char **args, char **envp)
{
	t_token	*tokens;
	int	result;
	
	(void)envp;
	tokens = create_token_from_args(args);
	result = ft_echo(tokens);
	free_tokens(tokens);
	return result;
}

int adapter_cd(char **args, char **envp)
{
	t_token	*tokens;
	int	result;

	tokens = create_token_from_args(args);
	result = ft_cd(tokens,(char ***)&envp);
	free_tokens(tokens);
	return result;
}

int adapter_pwd(char **args, char **envp)
{
	(void)args;
	(void)envp;
	return ft_pwd();
}

int adapter_env(char **args, char **envp)
{
	(void)args;
	return ft_env(envp);
}
