/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 09:22:29 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/09 12:55:31 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdio.h>

char	*resolve_relative_path(char *path, t_map_list *env, char *str_temp)
{
	char	cwd[800];
	char	*resolved_path;

	(void)str_temp;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_getcwd_error());
	resolved_path = (char *)ft_calloc(ft_strlen(cwd) + ft_strlen(path) + 2, 1);
	ft_strcat(resolved_path, cwd);
	ft_strcat(resolved_path, "/");
	ft_strcat(resolved_path, path);
	if (access(resolved_path, F_OK) != 0)
	{
		free(resolved_path);
		perror("minishell: cd");
		return (NULL);
	}
	export_pwd_oldpwd(resolved_path, env, cwd, path);
	return (resolved_path);
}

char	*ft_getcwd_error(void)
{
	perror("cd: error retrieving current directory: getcwd: cannot \
			access parent directories");
	return (NULL);
}

char	*resolve_path(char *path, t_map_list *env)
{
	if (path[0] == '/')
		return (resolve_absolute_path(path, env, 0));
	else if (ft_strcmp(path, "..") == 0 || ft_strcmp(path, "../") == 0)
		return (resolve_up_path(path, env));
	else
		return (resolve_relative_path(path, env, 0));
}

int	manage_cd_home(char *home, char **temp, t_map_list *env)
{
	char	cwd[800];

	home = ft_getenv("HOME", env, 0);
	if (home == NULL)
		return (1);
	if (chdir(home) != 0)
		return (ft_cd_root_dir_error(home));
	if (home)
		free(home);
	temp[1] = buildin_cd_add_pwd(env);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_cd_getcwd_error(&temp[1]));
	if (temp[1])
		free(temp[1]);
	return (0);
}

int	buildin_cd(t_exec *data, t_map_list *env)
{
	char	*temp[3];
	char	*res_path;
	int		cd_back;
	char	*home;

	home = NULL;
	cd_back = 0;
	if(ft_lstsize(data->cmd) > 2)
		return(0);
	if (data->cmd->next == 0 || data->cmd->next->s == 0
		|| data->cmd->next->s[0] == 0)
		return (manage_cd_home(home, temp, env));
	else if (data->cmd->next && data->cmd->next->s \
			&& data->cmd->next->s[0] == '-' && \
			data->cmd->next->s[1] == 0 && \
			back_to_old_pwd(&cd_back, &res_path, \
			env) == 1)
		return (1);
	else if (cd_back != 1)
	{
		res_path = resolve_path(data->cmd->next->s, env);
		if (res_path == NULL)
			return (1);
	}
	return (buildin_cd_manage_return(&res_path, data));
}
