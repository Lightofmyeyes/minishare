/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 00:41:05 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/06 03:07:56 by lcosta-a         ###   ########.fr       */
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
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	QUOTE_S,
	QUOTE_D,

	TOKEN_EOF
} t_token_type;

typedef struct	s_token
{
	char	*value;
	t_token_type	type;
	struct s_token	*next;
} t_token;

t_token 	*tokenize(char *input);
void		skip_spaces(char **input);
int			is_operator(char c);
int			is_double_operator(char *input);
void		create_word_token(t_token **token, char **input);
void		create_operator_token(t_token **tokens, char **input);
t_token		*create_token(char *value, int len, t_token_type type);
void		add_token(t_token **tokens, t_token *new_token);
void		free_tokens(t_token *tokens);
void		print_tokens(t_token *tokens);

#endif
