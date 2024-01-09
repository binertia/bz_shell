/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:59:27 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/06 23:54:40 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_cv_fake_condition(t_tok_list *list)
{
	if (((ft_strcmp("|", list->str) == 0 || \
			ft_strcmp("||", list->str) == 0 || \
			ft_strcmp("&&", list->str) == 0)) == 0)
		return (1);
	return (0);
}

int	check_condition_valid(t_tok_list *list)
{
	int	buf;

	buf = 0;
	if (setup_and_run_check_for_child(list, &buf))
		return (1);
	while (list)
	{
		if (list->child)
		{
			buf = check_condition_valid(list->child);
			if (buf)
				return (1);
		}
		else if (list->token == CONDITION_TYPE)
		{
			if (check_cv_fake_condition(list) == 1)
				return (fake_condition(list));
			if ((list->next && list->next->token == CONDITION_TYPE)
				|| list->next == NULL)
				return (dup_or_nullafter_condition(list));
		}
		list = list->next;
	}
	return (0);
}
