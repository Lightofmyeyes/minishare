/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:31:27 by lcosta-a          #+#    #+#             */
/*   Updated: 2026/01/07 18:26:50 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "executor.h"
#include "env_utils.h"
#include "ast_utils.h"
#include "ast_converter.h"
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

extern char **environ;
static void	init_readline(void);

int	main(void)
{
	char	*input;
	char	**my_envp;
	int		exit_status;
	int		result;
	t_node	*ast;
	t_token	*tokens;
	t_list	*env_list;

	exit_status = 0;
	my_envp = copy_envp(environ);
	if (!my_envp)
		return (1);
	printf("DEBUG: my_envp[0] = %s\n", my_envp[0]);
	env_list = convert_envp_to_env_list(my_envp);
	printf("DEBUG: convert_envp_to_env_list concluído\n");
	init_readline();
	printf("DEBUG: antes do readline\n");
	while (1)
	{
		input = readline("miniconcha> ");
		if (!input)
		{
			printf("\n");
			break ;
		}
		if (input[0])
			add_history(input);
		tokens = tokenize(input);
		ast = create_ast_from_tokens(tokens, env_list);
		if (ast)
		{
			if (ast->type == AST_PIPE)
			{
				execute_tree(ast);
				free_ast(ast);
				rl_cleanup_after_signal();
				rl_replace_line("", 0);
				rl_on_new_line();
				rl_redisplay();
				continue;
			}
			if (ast->type == BUILTIN)
			{
				result = execute_builtin(tokens, &my_envp, &exit_status);
				if (result == -2)
				{
					free_ast(ast);
					break;
				}
			}
			else
			{
				execute_tree(ast);
			}
			free_ast(ast);
		}
		free_tokens(tokens);
		free(input);
	}
	free_envp(my_envp);
	free_env_list(env_list);
	return exit_status;
}

static void init_readline(void)
{
	rl_catch_signals = 0;
	using_history();
}
