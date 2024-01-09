/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:52:47 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 16:40:39 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	char_valid(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || \
			c == '+' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	handle_delimiter(char *cmd, size_t *i, int *append)
{
	while (cmd[*i] && cmd[*i] != '=')
	{
		if (char_valid(cmd[*i]) == 0)
			return (0);
		if (cmd[*i] == '+')
		{
			if (cmd[*i + 1] && cmd[*i + 1] == '=')
				*append = 1;
			else
				return (0);
		}
		*i += 1;
	}
	return (1);
}

int	check_export_valid(char *cmd)
{
	size_t	i;
	int		append;

	append = 0;
	i = 0;
	if (ft_strchr("!@#$%^&*()+=\\-\"'{[]}$?&:;~`.,/*1234567890", cmd[0]))
		return (0);
	if (handle_delimiter(cmd, &i, &append) == 0)
		return (0);
	if (i == 0)
		return (0);
	else if (i == 1)
	{
		if (ft_strchr("!@#$%^&*()+=\\-\"'{[]}$?&:;~`.,/*", cmd[0]))
			return (0);
	}
	if (ft_strchr(cmd, '=') == NULL)
		return (3);
	if (append == 1)
		return (2);
	return (1);
}

void	print_export(t_map_list *env)
{
	while (env)
	{
		if (env->key && ft_strcmp(env->key, "_PWD"))
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}
