/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 03:09:12 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/06 03:11:05 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_utils.h"
#include "libft/libft.h"

void	free_ast(t_node *ast)
{
	char	**cmd;
	
	if (!ast)
		return;
	if (ast->type == AST_PIPE)
	{
		free_ast(ast->left);
		free_ast(ast->right);
	}
	else
	{
		if (ast->cmds)
		{
			cmd = ast->cmds;
			while (*cmd)
				free(*cmd++);
			free(ast->cmds);
		}
	}
	free(ast);
}
