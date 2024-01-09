/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:50:30 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:28:30 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_extra_redir_errfour(t_tok_list *temp_list, t_tok_list *list)
{
	if (list->next->str && list->next->str[0] == '&')
	{
		ft_free_tok_list(temp_list);
		temp_list = NULL;
		write(
			2,
			"minishell : syntax error near unexpected token `",
			48);
		write(2, &list->str[0], 1);
		write(2, "`\n", 2);
		return (0);
	}
	return (1);
}

int	check_extra_redir_errsix(t_tok_list *temp_list, t_tok_list *list)
{
	(void)list;
	ft_free_tok_list(temp_list);
	temp_list = NULL;
	write(2, "minishell : syntax error near unexpected token `", 48);
	write(2, "newline", 7);
	write(2, "`\n", 2);
	return (0);
}

int	sorry_i_no_have_name_left(t_tok_list *temp_list, t_tok_list *list)
{
	if (list->next && list->next->token == ARGS_TYPE)
	{
		if (check_extra_redir_errfour(temp_list, list) == 0)
			return (0);
		return (1);
	}
	else
		return (check_extra_redir_errsix(temp_list, list));
}

int	check_all_condition(t_tok_list *temp_list, t_tok_list *list, int *i)
{
	if (list->str[*i] && list->str[*i] == '&' && list->str[*i + 1] && \
		(list->str[*i + 1] == '<' || (list->str[*i + 1] == '>' && \
		list->str[*i + 2] && list->str[*i + 2] == '>')))
		return (check_extra_redir_errtwo(temp_list));
	while (list->str[*i] && ft_strchr("><", list->str[*i]) == 0)
		*i += 1;
	while (list->str[*i] && ft_strchr("><", list->str[*i]))
		*i += 1;
	if (list->str[*i])
	{
		if (check_extra_redir_errthree(temp_list, list->str, *i) == 0)
			return (0);
		return (1);
	}
	else
	{
		if (sorry_i_no_have_name_left(temp_list, list) == 0)
			return (0);
		return (1);
	}
}
