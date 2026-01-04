/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 05:09:53 by lcosta-a          #+#    #+#             */
/*   Updated: 2026/01/04 07:02:36 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return count;
}

char	**tokens_to_args(t_token *tokens)
{
	int		count;
	char	**args;
	int		i;

	count = count_args(tokens);
	args = malloc((count + 1) * sizeof(char *));
	if (!args)
		return NULL;
	i = 0;
	while (tokens && i < count)
	{
		if (tokens->type == WORD)
		{
			args[i] = ft_strdup(tokens->value);
			if (!args[i])
			{
				free_args(args);
				return NULL;
			}
			i++;
		}
		tokens = tokens->next;
	}
	args[i] = NULL;
	return args;
}

char **token_array_to_string_array(t_token *tokens)
{
	int	count;
	t_token	*tmp;
	char	**result;
	int		i;

	count = 0;
	tmp = tokens;
	while(tmp)
	{
		count++;
		tmp = tmp->next;
	}
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return NULL;
	tmp = tokens;
	i = 0;
	while (i < count)
	{
		result[i] = ft_strdup(tmp->value);
		if (!result[i])
		{
			free_string_array(result);
			return NULL;
		}
		tmp = tmp->next;
		i++;
	}
	result[count] = NULL;
	return result;
}
