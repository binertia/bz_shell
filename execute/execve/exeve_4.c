/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeve_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:14:22 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:24:40 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_and_exit(int *pipefd)
{
	close(pipefd[0]);
	exit(EXIT_FAILURE);
}

void	start_pipe(t_exec *data, int *status, t_map_list *env, int *std)
{
	int			pipefd[2];
	pid_t		pid[2];
	int			new_status[2];

	(void)std;
	setup_start_pipe(pid, pipefd, new_status, status);
	if (pid[0] == 0)
		manage_first_pipe_child(pipefd, data, new_status, &env);
	else
	{
		close(pipefd[1]);
		pid[1] = fork();
		if (pid[1] == 0)
		{
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
				close_and_exit(pipefd);
			close(pipefd[0]);
			execute_recursive(data->next, &new_status[1], &env, 1);
			exit(EXIT_FAILURE);
		}
		else
			manage_parent_waitchild(status, pid, pipefd);
	}
}
