/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 03:09:12 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/06 03:11:05 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *tokenize(char *input)
{
	t_token *tokens = NULL;

	while (*input)
	{
		skip_spaces(&input);
		if (is_operator(*input))
			create_operator_token(&tokens, &input);
		else
			create_word_token(&tokens, &input);
	}
	return tokens;
}
