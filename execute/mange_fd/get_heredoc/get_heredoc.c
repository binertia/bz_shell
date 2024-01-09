/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:40:50 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:40:12 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	get_heredoc(t_exec *head, t_map_list *env, int *status)
{
	t_exec		*exec_temp;

	if (head == NULL)
		return (0);
	exec_temp = head;
	while (exec_temp)
	{
		if (exec_temp->child)
		{
			if (get_heredoc(exec_temp->child, env, status) == 1)
				return (1);
		}
		if (exec_temp->redir)
		{
			if (get_heredoc_loop(exec_temp, status, env) == 1)
				return (1);
		}
		exec_temp = exec_temp->next;
	}
	return (0);
}
