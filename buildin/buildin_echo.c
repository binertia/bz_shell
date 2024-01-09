/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:01:22 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:41:50 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	buildin_echo(char **cmd)
{
	int		j;
	int		no_newline;

	j = 1;
	no_newline = 0;
	while (cmd[j] && ft_strcmp("-n", cmd[j]) == 0)
	{
		no_newline = 1;
		j++;
	}
	while (cmd[j])
	{
		printf("%s", cmd[j]);
		if (cmd[j + 1])
			printf(" ");
		j++;
	}
	if (no_newline == 0)
		printf("\n");
	return (0);
}
