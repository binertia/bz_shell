/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 00:27:01 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 00:27:47 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*update_oldpwd_str(t_map_list *env)
{
	char	*old_temp;
	char	*old_new;

	old_temp = ft_getenv("_PWD", env, 0);
	old_new = ft_calloc(ft_strlen(old_temp) + 8, 1);
	ft_strcat(old_new, "OLDPWD=");
	ft_strcat(old_new, old_temp);
	free(old_temp);
	return (old_new);
}

void	ps_export_back_old_pwd(char *old_path, t_map_list *env)
{
	char	*temp[5];
	char	*new;
	char	*ps_new;
	char	*old_new;

	new = ft_calloc(ft_strlen(old_path) + 5, 1);
	ps_new = ft_calloc(ft_strlen(old_path) + 6, 1);
	old_new = update_oldpwd_str(env);
	ft_strcat(new, "PWD=");
	ft_strcat(new, old_path);
	ft_strcat(ps_new, "_PWD=");
	ft_strcat(ps_new, old_path);
	temp[0] = "export";
	temp[4] = NULL;
	temp[1] = new;
	temp[2] = ps_new;
	temp[3] = old_new;
	buildin_export(env, temp, 0, 1);
	free(new);
	free(ps_new);
	free(old_new);
	new = NULL;
	ps_new = NULL;
	old_new = NULL;
}

int	error_access_return(char *path)
{
	if (access(path, F_OK) != 0)
	{
		perror("minishell: cd");
		free(path);
		return (1);
	}
	return (0);
}

char	*resolve_absolute_path(char *path, t_map_list *env, char *str_temp)
{
	char	cwd[800];
	char	*temp[3];
	char	*resolved_path;

	resolved_path = ft_strdup(path);
	if (access(resolved_path, F_OK) != 0)
	{
		free(resolved_path);
		return (perror("minishell: cd"), NULL);
	}
	update_pwd_str(resolved_path, env);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (resolved_path);
	str_temp = ft_calloc(ft_strlen(cwd) + 8, 1);
	strcat(str_temp, "OLDPWD=");
	strcat(str_temp, cwd);
	temp[0] = "export";
	temp[2] = NULL;
	temp[1] = str_temp;
	buildin_export(env, temp, 0, 0);
	free(str_temp);
	return (resolved_path);
}
