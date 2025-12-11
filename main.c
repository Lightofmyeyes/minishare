/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:31:27 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/10 19:32:12 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include <unistd.h>

extern char **environ;

int	main(void)
{
	char	*input;
	char	**my_envp;
	int		exit_status;
	int		result;

	exit_status = 0;
	my_envp = copy_envp(environ);
	if (!my_envp)
		return (1);
	while (1)
	{
		input = readline("miniconcha> ");
		if (!input)
			break ;
		if (input[0])
			add_history(input);
		t_token	*tokens = tokenize(input);
		if (tokens && is_builtin(tokens->value) != NOT_BUILTIN)
		{
			result = execute_builtin(tokens, &my_envp, &exit_status);
			if (is_builtin(tokens->value) == EXIT && result == 0)
				break;
		}
		else
			print_tokens(tokens);
		free_tokens(tokens);
		free(input);
	}
	free_envp(my_envp);
	return exit_status;
}
