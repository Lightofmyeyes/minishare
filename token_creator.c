/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 03:20:10 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/23 17:57:53 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	create_word_token(t_token **tokens, char **input)
{
	char	*start;
	int	len;
	char	*word;
	char 	original_char;

	original_char = **input;
	start = *input;
	if (**input == '"') 
	{
		printf("DEBUG: Processando aspas duplas\n");
		(*input)++;
		start = *input;
		while (**input && **input != '"')
			(*input)++;
		len = *input - start;
		if (**input == '"') 
			(*input)++;
	}
	else if (**input == '\'')
	{
		printf("DEBUG: Processando aspas simples\n");
		(*input)++;
		start = *input;
		while (**input && **input != '\'')
			(*input)++;
		len = *input - start;
		if (**input == '\'')
			(*input)++;
	}
	else
	{
		printf("DEBUG: Processando palavra sem aspas\n");
		while (**input && !is_space(**input) && !is_operator(**input))
			(*input)++;
		len = *input - start;
	}
	printf("DEBUG: Token criado: '%.*s' (tipo %c)\n", len, start, original_char);
	if (len > 0)
	{
		word = ft_substr(start, 0, len);
		add_token(tokens, create_token(word, len, WORD));
	}
}

void	create_operator_token(t_token **tokens, char **input)
{
	t_token_type	type;

	if (**input == '>' && *(*input + 1) == '>')
	{
		type = APPEND;
		*input += 2;

	}
	else if (**input == '<' && *(*input + 1) == '<')
	{
		type = HEREDOC;
		*input += 2;
	}
	else
	{
		if (**input == '|')
			type = PIPE;
		else if (**input == '>')
			type = TOK_OUT;
		else if (**input == '<')
			type = TOK_IN;
		(*input)++;
	}
	add_token(tokens, create_token(NULL, 0, type));
}
