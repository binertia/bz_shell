/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_run_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:15:15 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 20:31:51 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//----------- run_redir

void	setup_redir(t_redirect *redir, int *f_redir, int *b_redir, int *check)
{
	*check = 0;
	if (redir->front_fd)
	{
		if (redir->front_fd[0] == '&' && redir->front_fd[1] == 0)
			*f_redir = 3222;
		else
			*f_redir = ft_atoi(redir->front_fd);
	}
	else if (redir->type == O_REDIR || redir->type == APPEN)
	{
		*f_redir = STDOUT_FILENO;
		*b_redir = STDOUT_FILENO;
	}
	else if (redir->type == I_REDIR || redir->type == HERED)
	{
		*f_redir = STDIN_FILENO;
		*b_redir = STDIN_FILENO;
	}
	if (redir->back_fd && redir->back_fd[0] == '&' && redir->back_fd[1] \
			&& ft_strchr("0123456789", redir->back_fd[1]) && \
			redir->back_fd[2] == 0)
		*check = 1;
}

void	add_case_ampersand(t_redirect *redir, int *b_redir, char **file_name,
		int *check)
{
	if (redir->back_fd[1] && ft_strnum(redir->back_fd + 1))
	{
		*check = 1;
		*b_redir = ft_atoi(redir->back_fd + 1);
	}
	else
		*file_name = ft_strdup(redir->back_fd + 1);
}

int	bad_dollar_sign_usage(t_redirect *redir)
{
	if (redir->back_fd[0] == '$' && redir->back_fd[1])
	{
		write(2, "bash: ", 6);
		write(2, redir->back_fd, ft_strlen(redir->back_fd));
		write(2, ": ambiguous redirect\n", 21);
		return (1);
		return (EXIT_FAILURE);
	}
	return (0);
}

void	unquote_and_add_target_fd_ref(t_redirect *redir, int *b_redir,
		char **file_name, int *check)
{
	unquote_realloc_str(&(redir->back_fd));
	if (redir->back_fd[0] == '&')
		add_case_ampersand(redir, b_redir, file_name, check);
	else
		*file_name = ft_strdup(redir->back_fd);
}

void	getfd_ref_from_next_args(t_exec **data, t_map_list *env, int *status,
		char **file_name)
{
	*data = (*data)->next;
	replace_str(&(*data)->cmd->s, env, *status);
	unquote_realloc_str(&(*data)->cmd->s);
	*file_name = ft_strdup((*data)->cmd->s);
}
