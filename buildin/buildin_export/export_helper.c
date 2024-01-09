/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:02:30 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 18:53:43 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	setup_buildin_export(int *condition, size_t *j, char **res, char **cmd)
{
	(void)res;
	*j = 1;
	*condition = 0;
	if (cmd[1] == 0)
		return (1);
	return (0);
}
