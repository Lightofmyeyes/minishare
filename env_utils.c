/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:00:08 by lcosta-a          #+#    #+#             */
/*   Updated: 2026/01/04 11:04:42 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "libft/libft.h"
#include "env_utils.h"

void	print_env_list(t_list *env_list)
{
	t_list	*current;

	current = env_list;
	printf("=== ENV LIST ===\n");
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	printf("====================\n");
}

char **convert_env_list_to_envp(t_list *env_list)
{
	int	count;
	t_list	*current;
	char	**envp;
	int	i;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return NULL;
	current = env_list;
	i = 0;
	while (i < count)
	{
		envp[i] = ft_strdup(current->content);
		if (!envp[i])
		{
			while(i > 0)
				free(envp[--i]);
			free(envp);
			return NULL;
		}
		current = current->next;
		i++;
	}
	envp[count] = NULL;
	return envp;
}

t_list	*convert_envp_to_env_list(char **envp)
{
	t_list	*env_list;
	int	i;
	char	*content;
	t_list	*new_node;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		content = ft_strdup(envp[i]);
		if (!content)
		{
			free_env_list(env_list);
			return NULL;
		}
		new_node = malloc(sizeof(t_list));
		if (!new_node)
		{
			free(content);
			free_env_list(env_list);
			return NULL;
		}
		new_node->content = content;
		new_node->next = env_list;
		env_list = new_node;
	}
	return env_list;
}

t_list *init_env_list(char **envp)
{
	t_list	*env_list;
	int		i;
	t_list	*new_node;

	i = 0;
	env_list = NULL;
	while(envp[i])
	{
		new_node = ft_lstnew(ft_strdup(envp[i]));
		if (!new_node)
		{
			free_env_list(env_list);
			return NULL;
		}
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return env_list;
}

void	free_env_list(t_list *env_list)
{
	t_list	*current;
	t_list	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

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
