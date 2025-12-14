/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_adapter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:31:27 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/10 19:32:12 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor.h"
#include "minishell.h"
#include "libft/libft.h"
#include "ast_converter.h"

int adapter_export(char **args, char **envp)
{
	t_token	*tokens;
	int	result;
	
	(void)envp;
	tokens = create_token_from_args(args);
	result = ft_export(tokens, (char ***)&envp);
	free_tokens(tokens);
	return result;
}

int adapter_unset(char **args, char **envp)
{
	t_token	*tokens;
	int	result;

	(void)envp;
	tokens = create_token_from_args(args);
	if (!tokens)
		return 1;
	result = ft_unset(tokens, (char ***)&envp);
	free_tokens(tokens);
	return result;
}

int adapter_exit(char **args, char **envp)
{
	t_token	*tokens;
	int	result;

	(void)envp;
	tokens = create_token_from_args(args);
	if (!tokens)
		return 1;
	result = ft_exit(tokens, NULL);
	free_tokens(tokens);
	return result;
}

t_token *create_token_from_args(char **args)
{
	t_token	*head;
	t_token	*current;
	int	i;
	t_token	*new_token;

	head = NULL;
	current = NULL;
	i = 0;

	while (args[i])
	{
		new_token =  create_token(ft_strdup(args[i]), 
				ft_strlen(args[i]), WORD);
		if (!new_token)
		{
			free_tokens(head);
			return NULL;
		}
		if (!head)
			head = new_token;
		else
			current->next = new_token;
		current = new_token;
		i++;
	}
	return head;
	
}
