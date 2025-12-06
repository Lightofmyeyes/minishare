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

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_double_operator(char *input)
{
	return ((input[0] == '>' && input[1] == '>') ||
			(input[0] == '<' && input[1] == '<'));
}
