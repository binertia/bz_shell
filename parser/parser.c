/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:58:06 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/04 11:53:06 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*parser(char *raw_data, t_map_list *env, int *status)
{
	char		*new;
	t_tok_list	*list;
	t_exec		*head;

	head = NULL;
	new = manage_string_space(raw_data);
	if (check_raw_str(new) == 0)
		return (NULL);
	list = group_per_exec(new);
	if (check_token_list(list) == 0)
		return (NULL);
	get_exec_data(list, &head);
	ft_free_tok_list(list);
	list = NULL;
	if (get_heredoc(head, env, status) == 1)
	{
		*status = 1;
		ft_free_exec(head);
		head = NULL;
		return (NULL);
	}
	if (check_addition_exec(head) == 0)
		return (NULL);
	return (head);
}

t_tok_list	*group_per_exec(char *src)
{
	t_tok_list	*tok_head;
	int			temp;

	temp = 0;
	tok_head = NULL;
	recursive_token(src, &tok_head, 1, 0);
	free(src);
	src = NULL;
	if (valid_raw_data(tok_head, &temp) != 0)
	{
		ft_free_tok_list(tok_head);
		tok_head = NULL;
		return (0);
	}
	return (tok_head);
}

int	valid_raw_data(t_tok_list *data, int *error)
{
	int	new_error;

	if (data == NULL)
		return (0);
	new_error = 0;
	if (data->token == ERROR_TYPE)
	{
		write(2, "minishell : syntax error unexpected token at `", 46);
		if (data->str)
			write(2, data->str, ft_strlen(data->str));
		else
			write(2, "<n/a>", 5);
		write(2, "`\n", 2);
		(*error)++;
		return (2);
	}
	error += valid_raw_data(data->child, error);
	error += valid_raw_data(data->next, error);
	return (new_error);
}
