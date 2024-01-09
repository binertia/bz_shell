/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:02:55 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/06 23:41:24 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	buildin_exit_args_err(int *status)
{
	write(2, "minishell: exit: too many arguments\n", 36);
	*status = 1;
	return (*status);
}

void	buildin_exit_alp_arg(char **cmd, int *status)
{
	write(2, "exit: ", 6);
	write(2, cmd[1], ft_strlen(cmd[1]));
	write(2, ": numeric argument required\n", 28);
	*status = 255;
}

int	buildin_exit(char **cmd, int *status)
{
	int	size;

	size = 0;
	while (cmd[size])
		size++;
	*status = 0;
	printf("exit\n");
	if (size == 1)
		return (*status + 512);
	else if (size > 2)
		return (buildin_exit_args_err(status));
	if (handle_over_llong(cmd[1]) != VALID_LLONG)
		*status = (unsigned char)handle_over_llong(cmd[1]);
	else if (ft_strnum_exit(cmd[1]))
		*status = (unsigned char)ft_atoll(cmd[1]);
	else if (cmd[1])
		buildin_exit_alp_arg(cmd, status);
	return (*status + 512);
}
