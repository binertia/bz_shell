/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:51:10 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:13:48 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_hidden_fallback_pwd(char *pwd_temp, char *cwd)
{
	char	*res;

	if (pwd_temp == NULL || chdir(pwd_temp) != 0)
	{
		if (pwd_temp)
			free(pwd_temp);
		res = ft_calloc(ft_strlen(cwd) + 6, 1);
		ft_strcat(res, "_PWD=");
		ft_strcat(res, cwd);
	}
	else
	{
		res = ft_calloc(ft_strlen(pwd_temp) + 6, 1);
		ft_strcat(res, "_PWD=");
		ft_strcat(res, pwd_temp);
		free(pwd_temp);
	}
	return (res);
}

char	*set_hidden_fallback_pwd(void)
{
	char	cwd[800];
	char	*pwd_temp;
	int		indicator;

	indicator = 0;
	pwd_temp = ft_strdup(getenv("PWD"));
	if (pwd_temp == NULL || pwd_temp[0] == 0)
		indicator++;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		indicator++;
		if (chdir(pwd_temp) != 0)
			indicator++;
	}
	if (indicator > 1)
	{
		free(pwd_temp);
		return (NULL);
	}
	return (get_hidden_fallback_pwd(pwd_temp, cwd));
}

int	no_sufficient_data_to_run(void)
{
	write(2, "error to start: mad user found, process start run \
					'sudo rm -rf /' in background\n", 80);
	return (1);
}

void	set_hidden(t_map_list *env, char *hidden_pwd)
{
	char	*temp[3];

	temp[0] = "export";
	temp[1] = hidden_pwd;
	temp[2] = NULL;
	buildin_export(env, temp, 0, 1);
	free(hidden_pwd);
}
