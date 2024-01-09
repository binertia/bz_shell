/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_run_dir_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:22:57 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/04 11:06:34 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_redir_appen(char *file_name, int f_redir)
{
	int	fd;

	if (ft_strchr(file_name, '/') && check_file_avaiable(file_name) == 1)
		return (EXIT_FAILURE);
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (f_redir == 3222)
		return (EXIT_FAILURE);
	else
	{
		if (fd == -1 || ft_dup2(f_redir, fd) == 1)
		{
			if (fd != -1)
				close(fd);
			write(2, "minishell: ", 11);
			if (file_name)
			{
				perror(file_name);
				free(file_name);
			}
			file_name = NULL;
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	run_redir_heredoc(char **file_name, t_redirect *redir)
{
	int	pipe_fd[2];

	if (*file_name)
	{
		free(*file_name);
		*file_name = NULL;
	}
	pipe(pipe_fd);
	if (fork() == 0)
	{
		close(pipe_fd[0]);
		if (redir->heredoc)
			write(pipe_fd[1], redir->heredoc, ft_strlen(redir->heredoc));
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe_fd[1]);
		wait(NULL);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	return (0);
}

int	manage_out_redir(char *file_name, int f_redir, int b_redir)
{
	if (f_redir == 3222)
	{
		if (run_redir_out_filename(file_name, b_redir) == 1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (run_solo_redir_out(file_name, f_redir, b_redir) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	start_run_redir(t_redirect **redir, char **file_name, int f_redir,
		int b_redir)
{
	if ((*redir)->type == I_REDIR)
	{
		if (run_redir_in(*file_name, f_redir) == 1)
			return (EXIT_FAILURE);
	}
	else if ((*redir)->type == O_REDIR)
	{
		if (manage_out_redir(*file_name, f_redir, b_redir) == 1)
			return (EXIT_FAILURE);
	}
	else if ((*redir)->type == APPEN)
	{
		if (run_redir_appen(*file_name, f_redir) == 1)
			return (EXIT_FAILURE);
	}
	else if ((*redir)->type == HERED)
		run_redir_heredoc(file_name, *redir);
	if (*file_name)
		free(*file_name);
	*file_name = NULL;
	*redir = (*redir)->next;
	return (EXIT_SUCCESS);
}

int	setup_run_redir(char **file_name, t_redirect **redir, t_exec *data)
{
	*redir = NULL;
	*file_name = NULL;
	if (data->redir == NULL)
		return (1);
	else
		*redir = data->redir;
	return (0);
}
