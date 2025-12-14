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
#include "executor.h"
#include "ast_utils.h"
#include "ast_converter.h"
#include <unistd.h>

extern char **environ;

int	main(void)
{
	char	*input;
	char	**my_envp;
	int		exit_status;
	t_node	*ast;
	t_token	*tokens;

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
		tokens = tokenize(input);
		ast = create_ast_from_tokens(tokens);
		if (ast)
		{
			if (ast->type == BUILTIN)
				execute_builtin(tokens, &my_envp, &exit_status);
			else
				execute_tree(ast);
			free_ast(ast);
		}
		free_tokens(tokens);
		free(input);
	}
	free_envp(my_envp);
	return exit_status;
}
