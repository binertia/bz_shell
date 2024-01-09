/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:13:23 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 18:26:56 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	make_full_cmd_path(int found, char **all_path, char **cmd_path, int i)
{
	if (found == 0)
		return (command_not_found_err(all_path, cmd_path));
	else if (found == 1)
		get_full_cmd_path(all_path[i], &cmd_path[0]);
	ft_free_chrarr(all_path);
	free(all_path);
	return (0);
}

int	get_status(int status)
{
	return ((status >> 8) & 0xFF);
}

int	manage_parent_waitchild(int *status, int *pid, int *pipefd)
{
	int	paren_status;

	setup_parent_waitchild(pipefd, &paren_status, pid);
	if (WIFEXITED(paren_status))
	{
		*status = get_status(paren_status);
	}
	else if (WIFSIGNALED(paren_status))
	{
		if (WTERMSIG(paren_status) == SIGINT)
		{
			printf("^C\n");
			*status = 130;
		}
		else if (WTERMSIG(paren_status) == SIGQUIT)
		{
			printf("^\\Quit: 3\n");
			*status = 131;
		}
	}
	return (*status);
}
