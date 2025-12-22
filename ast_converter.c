/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_converter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:31:27 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/22 16:43:19 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "libft/libft.h"

static	t_node *create_simple_command(t_token **tokens);

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
