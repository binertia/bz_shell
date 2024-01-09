/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:13:13 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/06 09:13:14 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_cmd_cmp_update_state(char *s1, char *s2, int *state)
{
	if (ft_strcmp(s1, s2) == 0)
	{
		*state = 1;
		return (1);
	}
	return (0);
}

void	close_dir_and_update(DIR **dir_p, struct dirent **entry, int *i)
{
	if (*dir_p)
		closedir(*dir_p);
	*dir_p = NULL;
	*entry = 0;
	*i += 1;
}

int	get_cmd_state(int *found, char **cmd_path, char **all_path, int i)
{
	struct dirent	*entry;
	DIR				*dir_p;

	while (all_path[i] && *found == 0)
	{
		dir_p = opendir(all_path[i]);
		if (dir_p != NULL)
		{
			entry = readdir(dir_p);
			while (entry != NULL)
			{
				if (get_cmd_cmp_update_state(cmd_path[0], entry->d_name,
						found) == 1)
					break ;
				entry = readdir(dir_p);
			}
		}
		if (*found == 1)
			break ;
		close_dir_and_update(&dir_p, &entry, &i);
	}
	if (dir_p != NULL)
		closedir(dir_p);
	return (i);
}

int	try_run_absolute_cmd(char **cmd_path, int *status, char **all_path)
{
	int	temp;

	temp = 0;
	temp = check_absolute_command(cmd_path, status);
	if (temp)
	{
		ft_free_chrarr(all_path);
		free(all_path);
		return (1);
	}
	return (0);
}

char	*get_full_cmd_path(char *path, char **cmd)
{
	char	*res;

	res = ft_calloc(ft_strlen(path) + ft_strlen(*cmd) + 2, 1);
	ft_strcat(res, path);
	ft_strcat(res, "/");
	ft_strcat(res, *cmd);
	free(*cmd);
	*cmd = res;
	return (res);
}
