/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:47:50 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 17:37:53 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_equal(char **cmd, int j)
{
	if (cmd[j] == NULL && cmd[j][0] == 0)
		return (1);
	return (0);
}

int	buildin_export(t_map_list *env, char **cmd, int status, int pscall)
{
	char	**res;
	size_t	j;
	int		condition;

	res = NULL;
	if (setup_buildin_export(&condition, &j, res, cmd) == 1)
		return (print_export(env), EXIT_SUCCESS);
	while (cmd[j])
	{
		condition = check_export_valid(cmd[j]);
		if ((condition && ft_strstr(cmd[j], "_PWD") == 0) || \
				(ft_strstr(cmd[j], "_PWD") && pscall == 1))
		{
			if (check_equal(cmd, j) == 1)
				break ;
			if (condition == 1)
				export_one_condition(cmd, &j, res, env);
			else if (condition == 2)
				export_sec_condition(cmd, &j, res, env);
		}
		else
			buildin_export_error(cmd, j, &status);
		j++;
	}
	return (status);
}
