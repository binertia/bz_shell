/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:57:50 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:27:53 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_extra_redir(t_tok_list *list)
{
	int			i;
	t_tok_list	*temp_list;

	temp_list = list;
	while (list)
	{
		i = 0;
		if (list->child && check_extra_redir(list->child) == 0)
			return (check_extra_redir_errone(temp_list));
		if (list->token == REDIR_TYPE)
		{
			if (check_all_condition(temp_list, list, &i) == 0)
				return (0);
		}
		list = list->next;
	}
	return (1);
}

int	check_child_valid(t_tok_list *head)
{
	int			is_error;
	t_tok_list	*temp;

	if (head == NULL)
		return (0);
	is_error = 0;
	temp = head->child;
	if (temp)
		is_error += check_child_valid(temp);
	if (head)
	{
		if (head->token == 0)
		{
			if (head->str == 0 || head->str[0] == 0)
				is_error++;
		}
		if (head->token == ERROR_TYPE)
			return (1);
	}
	is_error += check_child_valid(head->next);
	return (is_error);
}

int	check_error_sticky_child(t_exec *head)
{
	int	i;

	i = 0;
	if (head->child)
		i += check_error_sticky_child(head->child);
	if (head->child && head->next && head->run_condition == 0)
		return (1);
	if (head->next)
		i += check_error_sticky_child(head);
	return (i);
}

int	child_valid_on_child(t_exec *head)
{
	if (head->child && check_child_valid_exec(head->child) == 0)
	{
		write(2, "minishell : syntax error near unexpected token `", 48);
		if (head->child->cmd && head->child->cmd->s)
			write(2, head->child->cmd->s, ft_strlen(head->child->cmd->s));
		else
			write(2, "(", 1);
		write(2, "`\n", 2);
		return (0);
	}
	return (1);
}

int	check_child_valid_exec(t_exec *head)
{
	while (head)
	{
		if (child_valid_on_child(head) == 0)
			return (0);
		if ((head->child && head->cmd) || (head->child && head->next
				&& head->run_condition == 0))
		{
			printf("in errorrr child next no condition\n");
			return (0);
		}
		if (head->child && head->cmd && head->cmd->s)
		{
			write(2, "minishell : syntax error near unexpected token `", 48);
			if (head->child->cmd && head->child->cmd->s)
				write(2, head->child->cmd->s, ft_strlen(head->child->cmd->s));
			else
				write(2, "(", 1);
			write(2, "`\n", 2);
			return (0);
		}
		head = head->next;
	}
	return (1);
}
