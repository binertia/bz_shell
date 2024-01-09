/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_parser_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:12:37 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/03 11:29:45 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_redir_len(t_redirect *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	ft_dup2(int f_redir, int b_redir)
{
	if (dup2(b_redir, f_redir) == -1)
	{
		perror("minishell");
		return (1);
	}
	return (0);
}
