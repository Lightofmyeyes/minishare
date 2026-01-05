/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:51:07 by fpedroso          #+#    #+#             */
/*   Updated: 2026/01/05 16:15:47 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "builtins_adapter.h"
#include "get_path.h"
#include "builtins.h"
#include "env_utils.h"
#include "handle_redirections.h"
#include <sys/wait.h>

static void	pipe_logic(t_node *node);
static void	exec_left(int pip[2], t_node *node);
static void	exec_right(int pip[2], t_node *node);
static void 	init_builtin_table(t_builtin table[N_BUILTINS]);
static void	exec_cmd(t_node *node);
static int	exec_forked_builtin(t_node *node);
static int	exec_builtin(t_node *node);

void    execute_tree(t_node *node)
{
	if (!node)
		return;
	if (node->type == AST_PIPE)
		pipe_logic(node);
	else
	{
		handle_redirections(node);
		if (node->type == EXT_CMD)
			exec_cmd(node);
		else if (node->is_pipeline && node->type == BUILTIN)
			exec_forked_builtin(node);
		else if (node->type == BUILTIN)
			exec_builtin(node);
		clean_temp_files(node);
	}
}

static int	exec_forked_builtin(t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == CHILD)
	{
		exec_builtin(node);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	return (1);
}

static int	exec_builtin(t_node *node)
{
	t_builtin	builtin_table[N_BUILTINS];
	int			i;
	char		**envp;
	int		result;
	int		stdin_backup;
	int		stdout_backup;
	int		stderr_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	stderr_backup = dup(STDERR_FILENO);

	init_builtin_table(builtin_table);
	i = 0;
	envp = convert_env_list_to_envp(node->env_list);
	if (!envp)
	{
		restore_stdinout(stdin_backup, stdout_backup, stderr_backup);
		return -1;
	}
	handle_redirections(node);
	while (i < N_BUILTINS)
	{
		if (ft_strcmp(node->cmds[0], builtin_table[i].name) == 0)
		{
			result = builtin_table[i].func(node->cmds, envp);
			free_envp(envp);
			restore_stdinout(stdin_backup, stdout_backup, stderr_backup);
			rl_cleanup_after_signal();
			rl_replace_line("", 0);
			rl_on_new_line();
			return result;
		}
		i++;
    	}
	free_envp(envp);
	restore_stdinout(stdin_backup, stdout_backup, stderr_backup);
	rl_cleanup_after_signal();
	rl_replace_line("", 0);
	rl_on_new_line();
	return -1;
}

static void	exec_cmd(t_node *node)
{
	pid_t	pid;
	char	*path;
	char	**envp;

	pid = fork();
	if (pid == CHILD)
	{
		envp = convert_env_list_to_envp(node->env_list);
		if (!envp)
		{
			perror("Failed to convert environment");
			exit(1);
		}
		path = get_path(node->cmds, node->env_list);
		if (execve(path, node->cmds, envp) == -1)
		{
			free_envp(envp);
			perror("Execve");
			exit(1);
		}
		free_envp(envp);
	}
	waitpid(pid, NULL, 0);
}

void    init_builtin_table(t_builtin table[N_BUILTINS])
{
    table[0].name = "echo";
    table[0].func = &adapter_echo;

    table[1].name = "cd";
    table[1].func = &adapter_cd;

    table[2].name = "pwd";
    table[2].func = &adapter_pwd;

    table[3].name = "export";
    table[3].func = &adapter_export;

    table[4].name = "unset";
    table[4].func = &adapter_unset;

    table[5].name = "env";
    table[5].func = &adapter_env;

    table[6].name = "exit";
    table[6].func = &adapter_exit;
}

static void	pipe_logic(t_node *node)
{
    pid_t	left_pid;
    pid_t	right_pid;
    int		pip[2];

	if (pipe(pip) != 0)
	{
		perror("Pipe");
		exit(1);
	}
	left_pid = fork();
	if (left_pid == CHILD)
	{
		exec_left(pip, node);
		exit(0);
	}
	close(pip[WRITE]);
	right_pid = fork();
	if (right_pid == CHILD)
	{
		exec_right(pip, node);
		exit(0);
	}
	close(pip[READ]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, NULL, 0);
	clean_temp_files(node);
}

static void	exec_left(int pip[2], t_node *node)
{
	close(pip[READ]);
	dup2(pip[WRITE], STDOUT_FILENO);
	close(pip[WRITE]);
	execute_tree(node->left);
	exit(0);
}

static void	exec_right(int pip[2], t_node *node)
{
	dup2(pip[READ], STDIN_FILENO);
	close(pip[READ]);
	execute_tree(node->right);
	exit(0);
}
