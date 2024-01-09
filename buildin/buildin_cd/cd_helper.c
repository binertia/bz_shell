/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:59:41 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 20:35:16 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	export_pwd_oldpwd(char *res_path, t_map_list *env, char *dir_path,
		char *target)
{
	char	*temp[3];
	char	*str_temp;
	char	*pwd_temp;

	(void)dir_path;
	(void)target;
	temp[0] = "export";
	temp[2] = NULL;
	pwd_temp = ft_getenv("PWD", env, 0);
	str_temp = (char *)ft_calloc(ft_strlen(pwd_temp) + 8, 1);
	ft_strcat(str_temp, "OLDPWD=");
	ft_strcat(str_temp, pwd_temp);
	free(pwd_temp);
	temp[1] = str_temp;
	buildin_export(env, temp, 0, 0);
	free(str_temp);
	update_pwd_str(res_path, env);
}

int	get_back_slash_n(char *src)
{
	int	count;

	count = 0;
	while (*src)
	{
		if (*src == '/' && src[1])
			count++;
		src++;
	}
	return (count);
}

char	*find_up_dir(char *src)
{
	char	*ptr;
	int		count;

	count = get_back_slash_n(src);
	ptr = src;
	while (count)
	{
		if (*ptr == '/')
		{
			if (ptr[1] && ptr[1] == '.' && ptr[2] && (ptr[2] == 0
					|| ptr[2] == '/'))
			{
				while (ptr > src)
				{
					ptr--;
					if (*ptr == '/')
						break ;
				}
			}
			count--;
		}
		ptr++;
	}
	return (ptr);
}

char	*resolve_up_path(char *path, t_map_list *env)
{
	char	cwd[800];
	char	*temp;
	char	*res;
	char	*ptr;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		temp = ft_getenv("PWD", env, 0);
	else
		temp = ft_strdup(cwd);
	ptr = find_up_dir(temp);
	res = ft_strndup(temp, ptr - temp);
	export_pwd_oldpwd(res, env, cwd, path);
	free(temp);
	return (res);
}
