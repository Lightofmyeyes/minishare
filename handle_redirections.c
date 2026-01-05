/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:33:42 by fpedroso          #+#    #+#             */
/*   Updated: 2026/01/05 16:22:40 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <fcntl.h>
#include "handle_redirections.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>

static void set_stdin_redir(t_redirection redirection);
static void set_stdout_redir(t_redirection redirection);
static void set_append_redir(t_redirection redirection);
static void set_heredoc_redir(t_node *node, char *heredoc_delim);
static void redir_error_message(void);
static int dup_file_into_stdin(char *heredoc_filepath);

void	handle_redirections(t_node *node)
{
	t_redirection_type	redir_type;
	int	i;

	i = 0;
	while (i < node->redirections_count)  
	{
		redir_type = node->redirections[i].type;
		if (redir_type == REDIR_IN)
			set_stdin_redir(node->redirections[i]);
		else if (redir_type == REDIR_OUT)
			set_stdout_redir(node->redirections[i]);
		else if (redir_type == REDIR_APPEND)
			set_append_redir(node->redirections[i]);
		else if (redir_type == REDIR_HEREDOC)
			set_heredoc_redir(node, node->redirections[i].target);
		else
		{
			redir_error_message();
			return;
		}
		i++;
	}
}

void restore_stdinout(int stdin_backup, int stdout_backup, int stderr_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	dup2(stderr_backup, STDERR_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	close(stderr_backup);
}

char *create_temp_file(t_node *node, char *delim)
{
	char	*filename;
	int	fd;
	char	*line;
	t_list	*new_node;

	filename = ft_strdup("/tmp/heredoc_XXXXXX");
	fd = mkstemp(filename);
	if (fd == -1)
	{
		perror("mkstemp");
		free(filename);
		return NULL;
	}
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	close(fd);
	new_node = ft_lstnew(filename);
	if (!new_node)
	{
		free(filename);
		return NULL;
	}
	ft_lstadd_back(&node->temp_files, new_node);
	return filename;
}	

static void	set_heredoc_redir(t_node *node, char *heredoc_delim)
{
	char	*heredoc_filepath;
	
	heredoc_filepath = create_temp_file(node, heredoc_delim);
	if (!heredoc_filepath)
	{
		perror("heredoc reader");
		return;
	}
	if (dup_file_into_stdin(heredoc_filepath) == -1)
		perror("heredoc dup2 failed");
}

static int	dup_file_into_stdin(char *heredoc_filepath)
{
	int	heredoc_fd;
	
	heredoc_fd = open(heredoc_filepath, O_RDONLY);
	if (heredoc_fd <  0)
	{
		perror("heredoc temp file");
		return -1;
	}
	if (dup2(heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("heredoc temp file");
		return -1;
	}
	if (close(heredoc_fd) < 0)
	{
		perror("heredoc temp file close");
		return -1;
	}
	return 0;
}

static void set_append_redir(t_redirection redirection)
{
	int	fd;

	fd = open(redirection.target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(redirection.target);
		return;
	}
	dup2(fd, STDOUT_FILENO);
	if (close(fd) < 0)
	{
		perror(redirection.target);
		return;
	}
}

static void set_stdout_redir(t_redirection redirection)
{
	int	fd;

	fd = open(redirection.target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(redirection.target);
		return;
	}
	dup2(fd, STDOUT_FILENO);
	if (close(fd) < 0)
	{
		perror(redirection.target);
		return;
	}
}

static void set_stdin_redir(t_redirection redirection)
{
	int	fd;

	fd = open(redirection.target, O_RDONLY);
	if (fd < 0)
	{
		perror(redirection.target);
		return;
	}
	dup2(fd, STDIN_FILENO);
	if (close(fd) < 0)
	{
		perror(redirection.target);
		return;
	}
}

static void redir_error_message(void)
{
	perror("Invalid redirection");
}

void	clean_temp_files(t_node *node)
{
	t_list	*current;
	t_list	*next;

	if (!node || !node->temp_files)
		return;
	current = node->temp_files;
	while (current)
	{
		next = current->next;
		if (current->content)
		{
			unlink((char *)current->content);
			free(current->content);
		}
		free(current);
		current = next;
	}
	node->temp_files = NULL;
}
