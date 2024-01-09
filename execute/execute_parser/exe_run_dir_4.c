/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_run_dir_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:25:10 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/04 11:07:35 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_env_len(t_map_list *env)
{
	size_t	res;

	res = 0;
	if (env->key)
		res += ft_strlen(env->key);
	res += 1;
	if (env->value)
		res += ft_strlen(env->value);
	res += 1;
	return (res);
}

char	**comply_env(t_map_list *env)
{
	char	**res;
	size_t	size;
	size_t	i;
	size_t	temp;

	size = ft_map_len(env);
	if (size == 0)
		return (NULL);
	res = (char **)ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (env)
	{
		if (ft_strstr(env->key, "_PWD=") == 0)
		{
			temp = ft_env_len(env);
			res[i] = (char *)ft_calloc(temp, 1);
			ft_strlcat(res[i], env->key, temp);
			ft_strlcat(res[i], "=", temp);
			if (env->value)
				ft_strlcat(res[i], env->value, temp);
			i++;
		}
		env = env->next;
	}
	return (res);
}

void	ft_free_chrarr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr[i]);
	arr = NULL;
}
