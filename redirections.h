/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso<fpedroso@student.42lisboa.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:52:35 by fpedroso          #+#    #+#             */
/*   Updated: 2025/11/22 16:52:35 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include <stdlib.h>
# include <unistd.h>

typedef enum e_redirection_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
} t_redirection_type;

typedef struct s_redirection
{
	t_redirection_type	type;
	char			*arg;
	char			*target;
} t_redirection;

typedef struct s_command
{
	char	**args;
	t_redirection	*redirections;
	int	redirections_count;
} t_command;

#endif
