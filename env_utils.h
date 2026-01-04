/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:00:08 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/10 18:05:41 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include "minishell.h"
# include "executor.h"

char	**convert_env_list_to_envp(t_list *env_list);
t_list	*convert_envp_to_env_list(char **envp);
void	free_env_list(t_list *env_list);
t_list	*init_env_list(char **envp);

#endif
