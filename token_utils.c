/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 03:34:21 by lcosta-a          #+#    #+#             */
/*   Updated: 2026/01/07 15:10:05 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

t_token	*create_token(char *value, int len, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (value && len > 0)
	{
		token->value = malloc(len + 1);
		if (!token->value)
		{
			free(token);
			return (NULL);
		}
		ft_strncpy(token->value, value, len);
		token->value[len] = '\0';
	}
	else
		token->value = NULL;
	token->type = type;
	token->next = NULL;
	return token;
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return;
	if (!*tokens)
	{
		*tokens = new_token;
		return;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	print_tokens(t_token *tokens)
{
	t_token	*current = tokens;

	while (current)
	{
		printf("Token: %s | Type: %d\n", current->value, current->type);
		current = current->next;
	}
}

t_token	*copy_token_list(t_token *start, t_token *end)
{
	t_token	*new_list;
	t_token	*current;
	t_token	*new_token;
	t_token	*last;

	new_list = NULL;
	current = start;
	last = NULL;
	while (current && current != end)
	{
		new_token = create_token(ft_strdup(current->value),
				ft_strlen(current->value),
				current->type);
		if (!new_token)
		{
			free_tokens(new_list);
			return NULL;
		}
		if (!new_list)
			new_list = new_token;
		else
			last->next = new_token;
		new_token->prev = last;
		last = new_token;
		current = current->next;
	}
	return new_list;	
}
