/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 03:20:10 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/06 03:54:51 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_word_token(t_token **tokens, char **input)
{
	char	*start = *input;
	int		in_quote = 0;
	char	quote_char = 0;

	while (**input)
	{
		if ((**input == '\'' || **input == '"') && !in_quote)
		{
			quote_char = **input;
			in_quote = 1;
			(*input)++;
			continue;
		}
		if (**input == quote_char && in_quote)
		{
			in_quote = 0;
			(*input)++;
			continue;
		}
		if (!in_quote && (**input == ' ' || **input == '\t' || is_operator(**input)))
			break;
		else
			(*input)++;
	}
	add_token(tokens, create_token(start, *input - start, WORD));
}

void	create_operator_token(t_token **tokens, char **input)
{
	t_token_type	type;

	if (is_double_operator(*input))
	{
		if ((*input)[0] == '>' && (*input)[1] == '>')
			type = APPEND;
		else
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
