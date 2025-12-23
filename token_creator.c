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
	char	quote;

	start = *input;
	while (**input && !is_operator(**input) && !ft_isspace(**input))
	{
		if (**input == '\'' || **input == '"')
		{
			quote = **input;
			(*input)++;
			while (**input && **input != quote)
				(*input)++;
			if (**input)
				(*input)++;
		}
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
