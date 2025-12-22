/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_from_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:43:36 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/22 18:52:27 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "libft/libft.h"

static t_redirection_type convert_token_to_redir_type(t_token_type type);
static char **token_array_to_cmd(t_token *tokens);

t_node *create_ast_from_tokens(t_token *tokens)
{
	t_node	*node;
	int		count;
	t_token	*temp;
	int		i;

	node = malloc(sizeof(t_node));
	if (!node)
		return NULL;
	ft_memset(node, 0, sizeof(t_node));
	node->redirections = NULL;
	node->redirections_count = 0;
	node->temp_files = NULL;

	count = 0;
	temp = tokens;
	while (temp)
	{
		if (is_redirection(temp->type))
			count++;
		temp=temp->next;
	}
	if (count > 0)
	{
		node->redirections = malloc(sizeof(t_redirection) * count);
		if (!node->redirections)
		{
			free(node);
			return NULL;
		}
		node->redirections_count = count;
		i = 0;
		temp = tokens;
		while (temp && i < count)
		{
			if (is_redirection(temp->type))
			{
				node->redirections[i].type = convert_token_to_redir_type(temp->type);
				node->redirections[i].target = ft_strdup(temp->next->value);
				i++;
			}
			temp = temp->next;
		}
	}
	if (tokens->type == WORD)
	{
		node->type = BUILTIN;
		node->cmds = token_array_to_cmd(tokens);
	}
	else if (tokens->type == PIPE)
	{
		node->type = AST_PIPE;
		node->left = create_ast_from_tokens(tokens);
		node->right = create_ast_from_tokens(tokens->next);
	}
	return node;
}

char	**token_array_to_cmd(t_token *tokens)
{
	int			count;
	t_token		*temp;
	char		**cmd;
	int			i;

	count = 0;
	temp = tokens;
	while (temp && temp->type == WORD)
	{
		count++;
		temp = temp->next;
	}
	cmd = malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return NULL;
	i = 0;
	temp = tokens;
	while (i < count)
	{
		cmd[i] = ft_strdup(temp->value);
		i++;
		temp = temp->next;
	}
	cmd[i] = NULL;
	return cmd;
}

t_redirection_type convert_token_to_redir_type(t_token_type type)
{
	if (type == TOK_IN)
		return REDIR_IN;
	else if (type == TOK_OUT)
		return REDIR_OUT;
	else if (type == APPEND)
		return REDIR_APPEND;
	else if (type == HEREDOC)
		return REDIR_HEREDOC;
	return REDIR_INVALID;
}
