/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:54:49 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 00:30:29 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	append_env(char **add, char **data, t_map_list *env)
{
	ft_strcat(*add, env->value);
	ft_strcat(*add, data[1]);
	if (env->value)
		free(env->value);
	env->value = *add;
}

int	is_env_dup(t_map_list *env, char **data, int condition)
{
	char	*new;

	while (env)
	{
		if (ft_strcmp(env->key, data[0]) == 0)
		{
			if (condition == 1)
			{
				new = ft_calloc(ft_strlen(env->value) + ft_strlen(data[1]) + 1,
						1);
				append_env(&new, data, env);
			}
			else
			{
				if (env->value)
					free(env->value);
				if (data[1])
					env->value = ft_strdup(data[1]);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	setup_mem_for_one(char **res, char *cmd_temp, size_t temp)
{
	res[0] = ft_calloc(temp + 1, 1);
	res[1] = ft_calloc((ft_strlen(cmd_temp) - temp) + 1, 1);
	res[2] = NULL;
}

void	export_one_condition(char **cmd, size_t *j, char **res, t_map_list *env)
{
	int		i;
	char	*cmd_temp;
	size_t	temp;

	i = 0;
	cmd_temp = cmd[*j];
	temp = ft_strchr(cmd_temp, '=') - cmd[*j];
	res = (char **)ft_calloc(3, sizeof(char *));
	setup_mem_for_one(res, cmd_temp, temp);
	while (*cmd_temp != '=')
		res[0][i++] = *cmd_temp++;
	cmd_temp++;
	i = 0;
	while (*cmd_temp)
		res[1][i++] = *cmd_temp++;
	if (is_env_dup(env, res, 0) == 0)
		ft_add_maplist(&env, res);
	if (res)
	{
		ft_free_chrarr(res);
		free(res);
	}
	res = NULL;
}

void	setup_value(char **res, size_t temp, char *cmd_temp)
{
	res[0] = ft_calloc(temp + 2, 1);
	res[1] = ft_calloc((ft_strlen(cmd_temp) - temp) + 2, 1);
	res[2] = NULL;
}
