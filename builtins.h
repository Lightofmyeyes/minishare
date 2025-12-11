/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:01:30 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/07 16:04:25 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <limits.h>
# include <unistd.h>

typedef enum e_builtin_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NOT_BUILTIN
} t_builtin_type;

int	is_builtin(char *cmd);
int	execute_builtin(t_token *tokens, char ***envp, int *exit_status);
int	ft_echo(t_token *tokens);
int	ft_pwd(void);
int	ft_env(char **envp);
int	ft_cd(t_token *tokens, char ***envp);
int	ft_export(t_token *tokens, char ***envp);
int	ft_unset(t_token *tokens, char ***envp);
int	ft_exit(t_token *tokens, int *exit_status);

int	is_numeric(char *str);
int	unset_env_var(char *name, char ***envp);
int	set_env_var(char *name, char *value, char ***envp);
char	**ft_realloc(char **src, int old_size, int new_size);

char	*expand_tilde(char *path, char **envp);
char	*get_env_var(char *name, char **envp);

char	**copy_envp(char **src);
void	free_envp(char **envp);

#endif
