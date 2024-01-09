/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:18:34 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/03 13:18:37 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_fflush(int *std, int is_dup, int is_close, int is_flush)
{
	if (is_dup)
	{
		dup2(std[0], STDIN_FILENO);
		dup2(std[1], STDOUT_FILENO);
		dup2(std[2], STDERR_FILENO);
	}
	if (is_close)
	{
		close(std[0]);
		close(std[1]);
		close(std[2]);
	}
	if (is_flush)
	{
		write(STDIN_FILENO, "", 0);
		write(STDOUT_FILENO, "", 0);
		write(STDERR_FILENO, "", 0);
	}
}

void	set_dup_fd(int fd_close, int fd_open, int f_redir)
{
	close(fd_close);
	dup2(fd_open, f_redir);
	close(fd_open);
}
