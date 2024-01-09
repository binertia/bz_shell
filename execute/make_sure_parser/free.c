/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:59:53 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/03 12:59:56 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_cmd_list(t_list *head)
{
	if (head == NULL)
		return ;
	if (head->next)
	{
		ft_free_cmd_list(head->next);
		head->next = NULL;
	}
	if (head->s)
	{
		free(head->s);
		head->s = NULL;
	}
	free(head);
	head = NULL;
}

void	ft_free_redir_list(t_redirect *head)
{
	if (head == NULL)
		return ;
	if (head->next)
	{
		ft_free_redir_list(head->next);
		head->next = NULL;
	}
	if (head->front_fd)
	{
		free(head->front_fd);
		head->front_fd = NULL;
	}
	if (head->back_fd)
	{
		free(head->back_fd);
		head->back_fd = NULL;
	}
	if (head->heredoc)
	{
		free(head->heredoc);
		head->heredoc = NULL;
	}
	free(head);
	head = NULL;
}

void	ft_free_exec(t_exec *head)
{
	if (head == NULL)
		return ;
	if (head->child)
	{
		ft_free_exec(head->child);
		head->child = NULL;
	}
	if (head->next)
	{
		ft_free_exec(head->next);
		head->next = NULL;
	}
	if (head->redir)
	{
		ft_free_redir_list(head->redir);
		head->redir = NULL;
	}
	if (head->cmd)
	{
		ft_free_cmd_list(head->cmd);
		head->cmd = NULL;
	}
	free(head);
	head = NULL;
}
