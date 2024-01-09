/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_run_dir_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:12:13 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/06 23:48:24 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_err_write_err(char *file_name)
{
	write(2, "minishell: ", 11);
	perror(file_name);
}

int	extend_run_redir_out_file_name(char *file_name, int fd)
{
	if (fd == -1 || ft_dup2(STDOUT_FILENO, fd) == 1)
	{
		if (fd != -1)
			close(fd);
		else
			redir_err_write_err(file_name);
		if (file_name)
			free(file_name);
		return (EXIT_FAILURE);
	}
	if (fd == -1 || ft_dup2(STDERR_FILENO, fd) == 1)
	{
		if (fd != -1)
			close(fd);
		else
			redir_err_write_err(file_name);
		if (file_name)
			free(file_name);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (0);
}

int	run_redir_out_filename(char *file_name, int b_redir)
{
	int	fd;

	if (file_name)
	{
		if (ft_strchr(file_name, '/') && check_file_avaiable(file_name))
			return (EXIT_FAILURE);
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		return (extend_run_redir_out_file_name(file_name, fd));
	}
	else
	{
		if (ft_dup2(2, b_redir) == 1)
			return (1);
		if (ft_dup2(1, b_redir) == 1)
			return (1);
		return (0);
	}
}

int	extend_run_solo_redir_out(int f_redir, int fd, char *file_name)
{
	if (fd == -1 || ft_dup2(f_redir, fd) == 1)
	{
		if (fd != -1)
			close(fd);
		else
			redir_err_write_err(file_name);
		if (file_name)
			free(file_name);
		return (1);
	}
	close(fd);
	return (0);
}
