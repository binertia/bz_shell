/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:05:46 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/06 08:55:20 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	buildin_pwd(t_map_list *head)
{
	char	cwd[800];
	char	*pwd;

	pwd = ft_getenv("_PWD", head, 0);
	if (pwd == NULL)
	{
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	return (0);
}
