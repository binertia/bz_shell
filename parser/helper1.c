/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:38:56 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/06 09:38:57 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd_str(char *resolved_path, t_map_list *env)
{
	char	*temp[4];
	char	*str_temp;
	char	*new_pwd;

	str_temp = ft_calloc(ft_strlen(resolved_path) + 5, 1);
	new_pwd = ft_calloc(ft_strlen(resolved_path) + 6, 1);
	ft_strcat(str_temp, "PWD=");
	ft_strcat(str_temp, resolved_path);
	ft_strcat(new_pwd, "_PWD=");
	ft_strcat(new_pwd, resolved_path);
	temp[0] = "export";
	temp[1] = str_temp;
	temp[2] = new_pwd;
	temp[3] = NULL;
	buildin_export(env, temp, 0, 1);
	free(str_temp);
	free(new_pwd);
}
