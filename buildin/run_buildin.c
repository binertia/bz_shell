/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_buildin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:06:17 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 17:57:27 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_buildin_cmd(t_exec *data, int *status, t_map_list **env, char **cmd)
{
	if (ft_strcmp("echo", cmd[0]) == 0)
		*status = buildin_echo(cmd);
	if (ft_strcmp("cd", cmd[0]) == 0)
		*status = buildin_cd(data, *env);
	else if (ft_strcmp("pwd", cmd[0]) == 0)
		*status = buildin_pwd(*env);
	else if (ft_strcmp("export", cmd[0]) == 0)
		*status = buildin_export(*env, cmd, 0, 0);
	else if (ft_strcmp("unset", cmd[0]) == 0)
		*status = buildin_unset(env, cmd);
	else if (ft_strcmp("env", cmd[0]) == 0)
		*status = buildin_env(*env, cmd);
	else if (ft_strcmp("exit", cmd[0]) == 0)
		*status = buildin_exit(cmd, status);
}

int	check_buildin(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0)
		return (1);
	if (ft_strcmp("cd", cmd) == 0)
		return (1);
	else if (ft_strcmp("pwd", cmd) == 0)
		return (1);
	else if (ft_strcmp("export", cmd) == 0)
		return (1);
	else if (ft_strcmp("unset", cmd) == 0)
		return (1);
	else if (ft_strcmp("env", cmd) == 0)
		return (1);
	else if (ft_strcmp("exit", cmd) == 0)
		return (1);
	return (0);
}
