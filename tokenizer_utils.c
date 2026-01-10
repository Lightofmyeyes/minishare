/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 03:13:12 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/06 03:18:09 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char **input)
{
	while (**input && (**input == ' ' || **input == '\t'))
		(*input)++;
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

int	is_operator(char c)
{
	printf("DEBUG: is_operator('%c') = %d\n", c,
			(c == '|' || c == '>' || c == '<' || c == '&'));
	return (c == '|' || c == '>' || c == '<' || c == '&');
}

int	is_double_operator(char *input)
{
	if (!input|| !input[0] || !input[1])
		return 0;
	return ((input[0] == '>' && input[1] == '>') ||
			(input[0] == '<' && input[1] == '<'));
}
