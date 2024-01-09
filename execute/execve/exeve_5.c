/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeve_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:16:40 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:23:46 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_pipe_parent(t_exec *cmd, pid_t *parent, t_map_list **temp,
		int *pipefd)
{
	int	child_status;
	int	new_status;

	child_status = 0;
	close(pipefd[1]);
	parent[1] = fork();
	if (parent[1] == 0)
	{
		set_dup_fd(pipefd[1], pipefd[0], STDIN_FILENO);
		execute_recursive(cmd->next, &child_status, temp, 1);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[0]);
		waitpid(parent[0], NULL, 0);
		waitpid(parent[1], &new_status, 0);
		dup2(STDOUT_FILENO, parent[1]);
		close(pipefd[1]);
		if (cmd->redir)
			run_redir(cmd, *temp, 0, 0);
		ft_free_map_list(*temp);
		free(temp);
		return (get_status(new_status));
	}
}

void	execute_pipe_child(t_exec *cmd, int *status, t_map_list **env)
{
	pid_t		parent[2];
	int			pipefd[2];
	int			child_status[2];
	t_map_list	*temp;

	temp = copy_map_list(*env);
	pipe(pipefd);
	parent[0] = fork();
	if (parent[0] == 0)
	{
		set_dup_fd(pipefd[0], pipefd[1], STDOUT_FILENO);
		execute_recursive(cmd->child, &child_status[0], &temp, 1);
		exit(EXIT_FAILURE);
	}
	else
		*status = execute_pipe_parent(cmd, parent, &temp, pipefd);
}

void	execute_solo_child(t_exec *cmd, t_map_list *env, int *status)
{
	pid_t	parent;
	int		new_status;
	int		child_status;

	child_status = 0;
	parent = fork();
	if (parent == 0)
	{
		execute_recursive(cmd->child, &child_status, &env, 1);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(parent, &new_status, 0);
		if (cmd->redir)
			run_redir(cmd, env, 0, 0);
		if (EXIT_SUCCESS == new_status << 8)
			*status = new_status << 8;
		else
			*status = (((new_status) >> 8) & 0xFF);
	}
}

void	execute_next_cmd(t_exec *cmd, int *status, t_map_list **env, int *std)
{
	if (cmd->run_condition == PIPE && cmd->child == NULL)
		start_pipe(cmd, status, *env, std);
	else
	{
		if (cmd->run_condition == OP_OR)
		{
			if (cmd->child && *status != EXIT_SUCCESS)
				execute_recursive(cmd->next, status, env, 0);
			else if (run_cmd(cmd, status, env) != EXIT_SUCCESS)
				execute_recursive(cmd->next, status, env, 0);
		}
		else if (cmd->run_condition == OP_AND)
		{
			if (cmd->child && *status == EXIT_SUCCESS)
				execute_recursive(cmd->next, status, env, 0);
			else if (run_cmd(cmd, status, env) == EXIT_SUCCESS)
				execute_recursive(cmd->next, status, env, 0);
		}
	}
}

int	setup_execute(t_exec *cmd, int status)
{
	if (status > 500 || cmd == NULL)
		return (1);
	return (0);
}
