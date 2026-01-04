/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:41:05 by lcosta-a          #+#    #+#             */
/*   Updated: 2026/01/03 22:40:42 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum	e_token_type
{
	WORD,
	PIPE,
	TOK_IN,
	TOK_OUT,
	APPEND,
	HEREDOC,
	QUOTE_S,
	QUOTE_D,

	TOKEN_EOF
} t_token_type;

typedef enum e_redirection_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_INVALID,
} t_redirection_type;

typedef struct	s_token
{
	char	*value;
	t_token_type	type;
	struct s_token	*next;
} t_token;

typedef struct	s_redirection
{
	t_redirection_type	type;
	char	*arg;
	char	*target;
} t_redirection;

typedef struct s_command
{
	char	**args;
	t_redirection *redirections;
	int	redirections_count;
} t_command;

t_token 	*tokenize(char *input);
void		skip_spaces(char **input);
int			is_operator(char c);
int		is_redirection(t_token_type type);
int			is_double_operator(char *input);
void		create_word_token(t_token **token, char **input);
void		create_operator_token(t_token **tokens, char **input);
t_token		*create_token(char *value, int len, t_token_type type);
void		add_token(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);
void		print_tokens(t_token *tokens);
void		ft_free_split(char **split);

#endif
