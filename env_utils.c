/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:00:08 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/12/10 18:05:41 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

char **copy_envp(char **src)
{
	int	i;
	int	size;
	char	**dest;

	i = 0;
	size = 0;
	while (src[size])
		size++;
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < size)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			while (i > 0)
				free(dest[--i]);
			free(dest);
			return (NULL);
		}
		i++;
	}
	dest[size] = NULL;
	return (dest);
}

void free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
