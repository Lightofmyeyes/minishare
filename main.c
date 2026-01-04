/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:31:27 by lcosta-a          #+#    #+#             */
/*   Updated: 2026/01/04 11:03:01 by lcosta-a         ###   ########.fr       */
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
	env_list = init_env_list(my_envp);
	init_readline();
	while (1)
	{
		printf("DEBUG: Iniciando novo comando\n");
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
		printf("DEBUG: onde gwen colocou um ternário\n");
		if (ast)
		{
			if (ast->type == BUILTIN)
			{
				result = execute_builtin(tokens, &my_envp, &exit_status);
				printf("DEBUG: Builtin executado, resultado: %d\n", result);
				if (result == -2)
				{
					free_ast(ast);
					break;
				}
//				free_env_list(ast->env_list);
//				ast->env_list = convert_envp_to_env_list(my_envp);
			}
			else
			{
				printf("DEBUG: Executando comando externo\n");
				execute_tree(ast);
			}
			printf("DEBUG: Resetando readline\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			free_ast(ast);
		}
		printf("DEBUG: Loop concluido, voltando ao inicio\n");
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
