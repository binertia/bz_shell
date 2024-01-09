/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 00:28:50 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 00:30:10 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_sec_condition(char **cmd, size_t *j, char **res, t_map_list *env)
{
	int		i;
	char	*cmd_temp;
	size_t	temp;

	i = 0;
	cmd_temp = cmd[*j];
	temp = ft_strchr(cmd_temp, '+') - cmd[*j];
	res = (char **)ft_calloc(3, sizeof(char *));
	setup_value(res, temp, cmd_temp);
	while (*cmd_temp != '+')
		res[0][i++] = *cmd_temp++;
	cmd_temp += 2;
	i = 0;
	while (*cmd_temp)
		res[1][i++] = *cmd_temp++;
	if (is_env_dup(env, res, 1) == 0)
		ft_add_maplist(&env, res);
	if (res)
	{
		ft_free_chrarr(res);
		free(res);
	}
	res = NULL;
}

void	buildin_export_error(char **cmd, int index, int *status)
{
	write(STDERR_FILENO, "minishell: export: ", 19);
	write(STDERR_FILENO, cmd[index], ft_strlen(cmd[index]));
	write(STDERR_FILENO, ": not a valid identifier\n", 25);
	*status = 1;
}
