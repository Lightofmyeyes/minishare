/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_adapter.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:31:27 by lcosta-a          #+#    #+#             */
/*   Updated: 2026/01/04 07:22:15 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_ADAPTER_H
# define BUILTINS_ADAPTER_H

# include "executor.h"
# include "minishell.h"

int	adapter_echo(char **args, char **envp);
int	adapter_cd(char **args, char **envp);
int	adapter_pwd(char **args, char **envp);
int	adapter_env(char **args, char **envp);
int	adapter_export(char **args, char **envp);
int	adapter_unset(char **args, char **envp);
int	adapter_exit(char **args, char **envp);
t_token	*create_token_from_args(char **args);

#endif
