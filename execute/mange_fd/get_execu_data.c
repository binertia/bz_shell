/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execu_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:32:17 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 16:01:48 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_parent_type(t_tok_list *data, t_exec **temp, t_exec **head)
{
	get_exec_data(data->child, &(*temp)->child);
	if (data->next && data->next->token == PARENT_TYPE)
	{
		get_exec_data(data->next, &(*temp)->next);
		return (1);
	}
	else
	{
		if (data->next)
			get_exec_data(data->next, head);
		return (1);
	}
}

int	setup_get_exec_data(t_tok_list *data, t_exec **head)
{
	if (data == NULL)
		return (1);
	if (*head == NULL)
		*head = make_new_exec();
	return (0);
}

void	get_exec_data(t_tok_list *data, t_exec **head)
{
	t_exec	*temp;

	if (setup_get_exec_data(data, head) == 1)
		return ;
	temp = *head;
	while (data)
	{
		if (data->token == PARENT_TYPE && run_parent_type(data, &temp, \
					head) == 1)
			return ;
		else if (data->token == REDIR_TYPE)
			add_exec_redir(*head, &data);
		else if (data->token == CONDITION_TYPE)
		{
			(*head)->run_condition = get_condition(data->str);
			get_exec_data(data->next, &temp->next);
			return ;
		}
		else if (data->token == ARGS_TYPE)
		{
			ft_new_list_addback(&temp->cmd, data->str);
			data = data->next;
		}
	}
}

int	recheck_redir(t_tok_list *list)
{
	int	i;

	i = 0;
	if (list == NULL)
		return (0);
	if (list->token == REDIR_TYPE)
	{
		if (ft_strstr(list->str, ">>>"))
			i++;
		else if (ft_strstr(list->str, "<<<"))
			i++;
	}
	if (list->child)
		i += recheck_redir(list->child);
	if (list->next)
		i += recheck_redir(list->next);
	return (i);
}

int	check_child(char *s)
{
	if (s == 0 || *s == 0)
	{
		write(2, "minishell : syntax error near unexpected token `", 48);
		write(2, "newline", 7);
		write(2, "`\n", 2);
		return (0);
	}
	while (*s == ' ')
		s++;
	if (*s && (ft_strchr("()|/<>#", *s)))
	{
		write(2, "minishell : syntax error near unexpected token `", 48);
		write(2, s, 1);
		write(2, "`\n", 2);
		return (0);
	}
	return (1);
}

// int	check_redir_valid_error(int redir)
// {
// 	write(2, "minishell : syntax error unexpected token at `", 46);
// 	write(2, &redir, 1);
// 	write(2, "`\n", 2);
// 	return (0);
// }

// void	move_ptr_in_quote(int *token, char **str)
// {
// 	*token = **str;
// 	*str += 1;
// 	while (**str && **str != *token)
// 		*str += 1;
// 	if (*str == 0)
// 		*str -= 1;
// }
