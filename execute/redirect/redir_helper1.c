/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:33:56 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 16:53:03 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bad_filename(t_redirect *redir, char **file_name)
{
	(void)redir;
	if (*file_name == NULL || **file_name == 0)
	{
		if (*file_name)
			free(*file_name);
		write(2, "minishell: ", 11);
		write(2, " ", 1);
		write(2, ": ambiguous redirect\n", 21);
		return (EXIT_FAILURE);
	}
	return (0);
}
