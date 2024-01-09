/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 00:18:18 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 00:18:24 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_map_list(t_map_list *env)
{
	if (env == NULL)
		return ;
	if (env->next)
		ft_free_map_list(env->next);
	if (env->key)
	{
		free(env->key);
		env->key = NULL;
	}
	if (env->value)
	{
		free(env->value);
		env->value = NULL;
	}
	free(env);
	env = NULL;
}

void	clean_unused_cmd(t_exec **head, char **input)
{
	if (*head != NULL)
		ft_free_exec(*head);
	*head = NULL;
	*input = NULL;
}
