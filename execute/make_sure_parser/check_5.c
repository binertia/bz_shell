/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:59:06 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 18:26:03 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	child_and_condition_err(t_tok_list *head)
{
	write(2, "minishell : syntax error near unexpected token `", 48);
	if (head->str && head->str[0])
		write(2, head->str, ft_strlen(head->str));
	else
		write(2, "(", 1);
	write(2, "`\n", 2);
	return (1);
}

int	check_child_condition_valid(t_tok_list *head, int lock)
{
	if (head == 0)
		return (0);
	while (head)
	{
		if (head->token == PARENT_TYPE)
		{
			lock++;
			if (head->child && check_child_condition_valid(head->child, 1))
				return (1);
		}
		else if (head->token == CONDITION_TYPE)
			lock = 0;
		if (lock > 2)
			return (child_and_condition_err(head));
		head = head->next;
	}
	return (0);
}

int	check_raw_str(char *str)
{
	if (str == NULL || check_redir_valid(str) == 0
		|| check_paren_valid(str) == 0)
	{
		if (str)
			free(str);
		str = NULL;
		return (0);
	}
	return (1);
}

int	check_token_list(t_tok_list *list)
{
	if (list == NULL)
		return (0);
	if (check_extra_redir(list) == 0)
		return (0);
	if (check_child_valid(list) > 0)
	{
		write(2, "minishell: syntax error unexpected token `()'\n", 46);
		ft_free_tok_list(list);
		list = NULL;
		return (0);
	}
	if (check_condition_valid(list))
	{
		ft_free_tok_list(list);
		list = NULL;
		return (0);
	}
	if (check_child_condition_valid(list, 0))
	{
		ft_free_tok_list(list);
		list = NULL;
		return (0);
	}
	return (1);
}

int	check_addition_exec(t_exec *head)
{
	if (check_redir_valid_exec(head) == 0 || check_child_valid_exec(head) == 0)
	{
		if (head)
			ft_free_exec(head);
		head = NULL;
		return (0);
	}
	return (1);
}
