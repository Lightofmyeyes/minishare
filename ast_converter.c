/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:31:27 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/10 19:32:12 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "libft/libft.h"

static	t_node *create_simple_command(t_token **tokens);

t_node	*create_ast_from_tokens(t_token *tokens)
{
	t_node	*head;
	t_node	*current;
	t_node	*node;
	t_node	*pipe_node;

	head = NULL;
	current = NULL;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			pipe_node = malloc(sizeof(t_node));
			if (!pipe_node)
				return NULL;
			ft_memset(pipe_node, 0, sizeof(t_node));
			pipe_node->type = AST_PIPE;
			pipe_node->left = head;
			tokens = tokens->next;
			pipe_node->right = create_ast_from_tokens(tokens);
			return pipe_node;
		}
		node = NULL;
		if (tokens->type == WORD)
			node = create_simple_command(&tokens);
		else
			node = create_simple_command(&tokens);
		if (!node)
			return NULL;
		if (!head)
			head = node;
		else
			current->right = node;
		current = node;
		tokens = tokens->next;
	}
	return head;
}

static	t_node *create_simple_command(t_token **tokens)
{
	t_node	*node;
	int	argc;
	t_token	*temp;
	char	**argv;
	char	*dup;

	node = malloc(sizeof(t_node));
	if (!node)
		return NULL;
	ft_memset(node, 0, sizeof(t_node));
	node->type = BUILTIN;
	node->is_pipeline = 0;
	argc = 0;
	temp = *tokens;
	while (temp && (temp->type == WORD || is_redirection(temp->type)))
	{
		if (temp->type == WORD)
			argc++;
		temp = temp->next;
	}
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
	{
		free(node);
		return NULL;
	}
	argc = 0;
	temp = *tokens;
	while (temp && (temp->type == WORD || is_redirection(temp->type)))
	{
		if (temp->type == WORD)
		{
			dup = ft_strdup(temp->value);
			if (!dup)
			{
				while (argc > 0)
					free(argv[--argc]);
				free(argv);
				free(node);
				return NULL;
			}
			argv[argc++] = dup;
		}
		temp = temp->next;
	}
	argv[argc] = NULL;
	node->cmds = argv;
	node->env_list = NULL;
	return node;
}
