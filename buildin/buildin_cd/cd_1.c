/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:32:53 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/09 12:55:27 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

int	back_to_old_pwd(int *back, char **res_path, t_map_list *env)
{
	char	*str_temp;

	str_temp = ft_getenv("OLDPWD", env, 0);
	if (access(str_temp, F_OK) != 0)
	{
		free(str_temp);
		return (1);
	}
	if (str_temp == 0 || *str_temp == 0)
	{
		if (str_temp)
			free(str_temp);
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		return (1);
	}
	printf("%s\n", str_temp);
	ps_export_back_old_pwd(str_temp, env);
	*back = 1;
	*res_path = ft_strdup(str_temp);
	free(str_temp);
	return (0);
}

int	buildin_cd_manage_return(char **res_path, t_exec *data)
{
	if (*res_path == NULL)
		return (0);
	if (chdir(*res_path) != 0)
	{
		printf("%s\n", *res_path);
		free(*res_path);
		*res_path = NULL;
		write(2, "minishell: cd: ", 15);
		perror(data->cmd->next->s);
		return (1);
	}
	free(*res_path);
	*res_path = NULL;
	return (0);
}

int	ft_cd_getcwd_error(char **s)
{
	if (*s)
		free(*s);
	*s = NULL;
	perror("cd: error retrieving current directory: getcwd: cannot \
			access parent directories");
	return (1);
}

char	*buildin_cd_add_pwd(t_map_list *env)
{
	char	*temp[4];
	char	*str_temp;
	char	*res_temp;
	char	*hidden_pwd;

	temp[0] = "export";
	temp[3] = NULL;
	str_temp = ft_getenv("HOME", env, 0);
	res_temp = ft_calloc(ft_strlen(str_temp) + 5, 1);
	hidden_pwd = ft_calloc(ft_strlen(str_temp) + 6, 1);
	ft_strcat(res_temp, "PWD=");
	ft_strcat(res_temp, str_temp);
	ft_strcat(hidden_pwd, "_PWD=");
	ft_strcat(hidden_pwd, str_temp);
	temp[1] = res_temp;
	temp[2] = hidden_pwd;
	buildin_export(env, temp, 0, 1);
	if (temp[2])
		free(temp[2]);
	if (str_temp)
		free(str_temp);
	str_temp = NULL;
	temp[2] = NULL;
	return (res_temp);
}

int	ft_cd_root_dir_error(char *home)
{
	if (home)
		free(home);
	write(2, "minishell: cd: HOME not set\n", 28);
	return (0);
}
