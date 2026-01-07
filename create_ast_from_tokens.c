/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_from_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 16:43:36 by lcosta-a          #+#    #+#             */
/*   Updated: 2026/01/06 18:05:03 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "builtins.h"
#include "libft/libft.h"

static int has_pipe(t_token *tokens);
static t_node *create_pipe_ast(t_token *tokens, t_list *env_list);
static t_redirection *collect_redirections(t_token *tokens);
static t_token *remove_redirections(t_token *tokens);
static t_node *create_command_node(t_token *tokens, t_redirection *redirs, t_list *env_list);
static int count_redirections(t_redirection *redirs);
static t_redirection_type convert_token_to_redir_type(t_token_type type);
//static int is_word_token(t_token_type type);
static char **token_array_to_cmd(t_token *tokens);

t_node *create_ast_from_tokens(t_token *tokens, t_list *env_list)
{
	t_redirection	*redirs;
	t_token		*cmd_tokens;

	if (has_pipe(tokens))
		return create_pipe_ast(tokens, env_list);
	redirs = collect_redirections(tokens);
	cmd_tokens = remove_redirections(tokens);
	return create_command_node(cmd_tokens, redirs, env_list);
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

/*
static int is_word_token(t_token_type type)
{
	return (type == WORD);
}
*/

static int has_pipe(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == PIPE)
			return 1;
		tokens = tokens->next;
	}
	return 0;
}

static t_node *create_pipe_ast(t_token *tokens, t_list *env_list)
{
	t_node	*node;
	t_token	*pipe_token;
	t_token	*left_tokens;
	t_token	*right_tokens;
	t_token *prev;

	prev = NULL;
	node = malloc(sizeof(t_node));
	if (!node)
		return NULL;
	ft_memset(node, 0, sizeof(t_node));
	node->type = AST_PIPE;
	node->env_list = env_list;
	pipe_token = tokens;
	while (pipe_token && pipe_token->type != PIPE)
	{
		prev = pipe_token;
		pipe_token = pipe_token->next;
	}
	left_tokens = tokens;
	right_tokens = pipe_token->next;
	if (prev)
		prev->next = NULL;
	else
		left_tokens = NULL;
	node->left = create_ast_from_tokens(left_tokens, env_list);
	node->right = create_ast_from_tokens(right_tokens, env_list);
	return node;
}

static t_redirection *collect_redirections(t_token *tokens)
{
	int		count;
	t_token		*temp;
	t_redirection	*redirs;
	int		i;

	count = 0;
	temp = tokens;
	while(temp)
	{
		if (is_redirection(temp->type))
			count++;
		temp = temp->next;
	}
	redirs = malloc(sizeof(t_redirection) * count);
	if (!redirs)
		return NULL;
	i = 0;
	temp = tokens;
	while (temp && i < count)
	{
		if (is_redirection(temp->type))
		{
			redirs[i].type = convert_token_to_redir_type(temp->type);
			redirs[i].target = ft_strdup(temp->next->value);
			i++;
		}
		temp = temp->next;
	}
	return redirs;
}

static t_token *remove_redirections(t_token *tokens)
{
	t_token	*new_tokens;
	t_token	*current;
	t_token	*new_token;

	new_tokens = NULL;
	current = tokens;
	while (current)
	{
		if (!is_redirection(current->type))
		{
			new_token = create_token(ft_strdup(current->value),
					ft_strlen(current->value), current->type);
			if (!new_token)
			{
				free_tokens(new_tokens);
				return NULL;
			}
			add_token(&new_tokens, new_token);
		}
		current = current->next;
	}
	return new_tokens;
}

static t_node *create_command_node(t_token *tokens, t_redirection *redirs, t_list *env_list)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return NULL;
	ft_memset(node, 0, sizeof(t_node));
	node->env_list = env_list;
	node->redirections = redirs;
	if (redirs)
		node->redirections_count = count_redirections(redirs);
	else
		node->redirections_count = 0;
	if (tokens && tokens->type == WORD)
	{
		if (is_builtin(tokens->value))
			node->type = BUILTIN;
		else
			node->type = EXT_CMD;
		node->cmds = token_array_to_cmd(tokens);
	}
	else
	{
		free(node);
		return NULL;
	}
	return node;
}

static int count_redirections(t_redirection *redirs)
{
	int	count;

	count = 0;
	while (redirs && redirs[count].target)
		count++;
	return count;
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
