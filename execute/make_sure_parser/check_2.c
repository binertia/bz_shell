/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:48:23 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/06 23:51:43 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	no_file_name_or_redir_num(t_exec *node)
{
	write(
		2,
		"minishell : syntax error near unexpected token `",
		48);
	if (node->next)
		write(2, " `\n", 3);
	else
		write(2, "newline`\n", 9);
	return (0);
}

int	check_redir_valid_exec(t_exec *node)
{
	t_redirect	*temp;

	while (node)
	{
		if (node->redir)
		{
			temp = node->redir;
			while (temp)
			{
				if (temp->back_fd == 0 || \
					(temp->back_fd && temp->back_fd[0] == 0))
				{
					if (node->next && node->next->cmd && \
						node->next->cmd->s && node->next->cmd->s[0] \
						&& node->next->child == NULL)
						return (1);
					else
						return (no_file_name_or_redir_num(node));
				}
				temp = temp->next;
			}
		}
		node = node->next;
	}
	return (1);
}

int	check_extra_redir_errone(t_tok_list *temp_list)
{
	if (temp_list)
	{
		ft_free_tok_list(temp_list);
		temp_list = NULL;
	}
	return (0);
}

int	check_extra_redir_errtwo(t_tok_list *temp_list)
{
	ft_free_tok_list(temp_list);
	temp_list = NULL;
	write(2, "minishell : syntax error near unexpected token `8`\n", 51);
	return (0);
}

int	check_extra_redir_errthree(t_tok_list *temp_list, char *str, int index)
{
	if (str[index] == '&' && str[index] == 0)
	{
		ft_free_tok_list(temp_list);
		temp_list = NULL;
		write(2, "minishell : syntax error near unexpected token `", 48);
		write(2, "newline", 7);
		write(2, "`\n", 2);
		return (0);
	}
	return (1);
}
