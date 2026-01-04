/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:52:35 by fpedroso          #+#    #+#             */
/*   Updated: 2026/01/04 10:09:00 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/ioctl.h>
#include "minishell.h"

#define READ	0
#define WRITE	1
#define CHILD		0
#define N_BUILTINS	7

typedef struct	s_builtin
{
    char	*name;
    int		(*func)(char **args, char **envp);
} t_builtin;

typedef enum	e_node_type
{
	AST_PIPE,
	EXT_CMD,
	BUILTIN,
	AND,
	OR
} t_node_type;

typedef struct	s_node
{
	t_node_type		type;
	struct s_node	*left;
	struct s_node	*right;
	char			**cmds;
	t_list			*env_list;
	t_list			*inline_env_list;
	bool			is_pipeline;
	t_redirection	*redirections;
	int				redirections_count;
	t_list			*temp_files;
} t_node;

void	execute_tree(t_node *node);
void	print_env_list(t_list *env_list);

#endif
