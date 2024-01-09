/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeve_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:31:08 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/09 11:49:20 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_normal_cmd_return_error(int *status)
{
	*status = 127;
	return (127);
}

void	run_normal_cmd_set_path(char **path)
{
	printf("->%d\n",*path[0] == 0);
	if (*path == NULL || **path == 0 || *path[0] == 0)
	{
		if (**path)
			free(*path);
		if (*path[0] == 0)
			free(*path);
		*path = ft_strdup("naughtyboy:andgirl");
	}
}

int	print_path_error(char *cmd, int *status)
{
	write(2, "minishell: ", 12);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	else
		write(2, " ", 1);
	write(2, " No such file or directory\n", 27);
	*status = 127;
	return (127);
}

int	run_normal_cmd(char **env_temp, int *status, t_map_list *env,
		char **cmd_path)
{
	t_helper_cmd	norm;

	norm.i = 0;
	norm.found = 0;
	norm.path = ft_getenv("PATH", env, 0);
	if ((norm.path == NULL || norm.path[0] == 0) && !ft_strchr(cmd_path[0],'/'))
	{
		free(norm.path);
		return (print_path_error(cmd_path[0], status));
	}
	// printf("*%d\n",norm.path[0] == 0);
	run_normal_cmd_set_path(&norm.path);
	norm.all_path = ft_split(norm.path, ':');
	free(norm.path);
	if (ft_strchr(cmd_path[0], '/'))
	{
		if (try_run_absolute_cmd(cmd_path, status, norm.all_path) == 1)
			return (1);
		norm.found = 2;
	}
	else
		norm.i = get_cmd_state(&norm.found, cmd_path, norm.all_path, 0);
	if (make_full_cmd_path(norm.found, norm.all_path, cmd_path, norm.i) != 0)
	{
		run_normal_cmd_return_error(status);
		return (1);
	}
	norm.i = execve_in_child(status, cmd_path, env_temp);
	return (norm.i);
}
