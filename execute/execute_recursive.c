/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_recursive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:24:07 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:23:00 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	end_child_cycle(t_exec **cmd, t_map_list **env, int status)
{
	if (*cmd)
	{
		ft_free_exec(*cmd);
		*cmd = NULL;
	}
	if (*env)
	{
		ft_free_map_list(*env);
		*env = NULL;
	}
	exit(status);
}

void	execute_recursive(t_exec *cmd, int *status, t_map_list **env, int child)
{
	int			std[3];

	if (setup_execute(cmd, *status) == 1)
		return ;
	if (cmd->child)
	{
		if (cmd->run_condition == PIPE)
			execute_pipe_child(cmd, status, env);
		else
			execute_solo_child(cmd, *env, status);
	}
	if (cmd->next)
		execute_next_cmd(cmd, status, env, std);
	else if (cmd->redir || cmd->cmd)
		run_cmd(cmd, status, env);
	if (child)
		end_child_cycle(&cmd, env, *status);
}
