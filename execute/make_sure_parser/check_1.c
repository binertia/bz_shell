/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:55:44 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/04 11:09:07 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	bad_condition_child(t_tok_list *list)
{
	if (list->token == CONDITION_TYPE && list->child == NULL)
	{
		write(2, "minishell : syntax error near unexpected token `", 48);
		if (list->str)
			write(2, list->str, ft_strlen(list->str));
		write(2, "`\n", 2);
		return (1);
	}
	return (0);
}

int	setup_buf_check_condition(t_tok_list *list, int *buf)
{
	*buf = 0;
	if (list->child)
	{
		*buf = check_condition_valid(list->child);
		if (*buf)
			return (1);
	}
	return (0);
}

int	fake_condition(t_tok_list *list)
{
	write(2, "minishell : syntax error near unexpected token `", 48);
	if (list->str)
		write(2, list->str, 1);
	write(2, "`\n", 2);
	return (1);
}

int	dup_or_nullafter_condition(t_tok_list *list)
{
	write(2, "minishell : syntax error near unexpected token `", 48);
	if (list->str)
		write(2, list->str, ft_strlen(list->str));
	write(2, "`\n", 2);
	return (1);
}

int	setup_and_run_check_for_child(t_tok_list *list, int *buf)
{
	if (setup_buf_check_condition(list, buf) == 1)
		return (1);
	if (bad_condition_child(list) == 1)
		return (1);
	return (0);
}
