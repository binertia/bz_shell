/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_run_dir_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:17:43 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/06 15:21:35 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_redir_in(char *file_name, int f_redir)
{
	int	fd;

	if (file_name)
	{
		fd = open(file_name, O_RDONLY);
		if (fd == -1)
		{
			write(2, "minishell: ", 11);
			perror(file_name);
			free(file_name);
			return (1);
		}
		if (ft_dup2(STDIN_FILENO, fd) == 1)
		{
			if (file_name)
				free(file_name);
			return (1);
		}
		close(fd);
	}
	else if (ft_dup2(0, f_redir) == 1)
		return (1);
	return (0);
}

int	check_file_avaiable(char *file_name)
{
	if (access(file_name, F_OK) == -1)
	{
		write(2, "minishell: ", 11);
		write(2, file_name, ft_strlen(file_name));
		write(2, ": No such file or directory\n", 29);
		if (file_name)
			free(file_name);
		file_name = NULL;
		return (1);
	}
	else if (access(file_name, W_OK) == -1)
	{
		write(2, "minishell: ", 11);
		if (file_name)
			write(2, file_name, ft_strlen(file_name));
		write(2, ": Permission denied\n", 20);
		if (file_name)
			free(file_name);
		return (1);
	}
	return (0);
}

int	run_solo_redir_out(char *file_name, int f_redir, int b_redir)
{
	int	fd;

	if (file_name)
	{
		if (ft_strchr(file_name, '/'))
		{
			if (check_file_avaiable(file_name) == 1)
				return (1);
		}
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (extend_run_solo_redir_out(f_redir, fd, file_name));
	}
	else
	{
		if (ft_dup2(f_redir, b_redir) == 1)
			return (1);
		return (0);
	}
}

int	try_run_ampersand_appen(int fd)
{
	if (fd == -1 || ft_dup2(2, fd) == 1)
	{
		if (fd != -1)
			close(fd);
		return (1);
	}
	if (fd == -1 || ft_dup2(1, fd) == 1)
	{
		if (fd != -1)
			close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
