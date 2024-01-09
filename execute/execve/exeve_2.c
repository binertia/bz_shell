/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeve_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:07:31 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 15:56:39 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	manage_run_cmd(t_exec *data, int *status, t_map_list **env)
{
	char	**cmd;
	char	**env_temp;
	int		checker[2];

	check_for_placeholder(checker, data->cmd->s);
	cmd = get_cmd_arr(data->cmd, *env, *status);
	if (cmd == NULL)
		return (no_cmd_to_run(checker, status, cmd));
	env_temp = comply_env(*env);
	if (check_buildin(data->cmd->s))
		run_buildin_cmd(data, status, env, cmd);
	else
		run_normal_cmd(env_temp, status, *env, cmd);
	if (cmd)
		ft_free_chrarr_with_ptr(cmd);
	if (env_temp)
		ft_free_chrarr_with_ptr(env_temp);
	return (*status);
}

int	run_cmd(t_exec *data, int *status, t_map_list **env)
{
	if (manage_redir(data, status, *env) == 1)
		return (EXIT_FAILURE);
	if (data->cmd && data->cmd->s)
		manage_run_cmd(data, status, env);
	return (*status);
}

void	setup_start_pipe(pid_t *pid, int *pipefd, int *new_status, int *status)
{
	new_status[0] = *status;
	new_status[1] = *status;
	pipe(pipefd);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid[0] = fork();
	signal(SIGINT, SIG_HOLD);
	signal(SIGQUIT, SIG_HOLD);
}

void	manage_first_pipe_child(int *pipefd, t_exec *data, int *new_status,
		t_map_list **env)
{
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	exit(run_cmd(data, &new_status[0], env));
}

void	setup_parent_waitchild(int *pipefd, int *paren_status, int *pid)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(pipefd[0]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], paren_status, 0);
	mod_sig_handle(sig_handler);
}

// int	manage_parent_waitchild(int *status, int *pid, int *pipefd)
// {
// 	int	paren_status;

// 	setup_parent_waitchild(pipefd, &paren_status, pid);
// 	if (WIFEXITED(paren_status))
// 	{
// 		*status = get_status(paren_status);
// 	}
// 	else if (WIFSIGNALED(paren_status))
// 	{
// 		if (WTERMSIG(paren_status) == SIGINT)
// 		{
// 			printf("^C\n");
// 			*status = 130;
// 		}
// 		else if (WTERMSIG(paren_status) == SIGQUIT)
// 		{
// 			printf("^\\Quit: 3\n");
// 			*status = 131;
// 		}
// 	}
// 	return (*status);
// }