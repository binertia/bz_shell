/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:35:28 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/04 11:49:01 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_back_fd(t_tok_list **data)
{
	char	*s;
	int		i;

	i = 0;
	s = (*data)->str;
	while (!(*(s + i) == '>' || *(s + i) == '<'))
		i++;
	while (*(s + i) == '>' || *(s + i) == '<')
		i++;
	if (*(s + i))
	{
		*data = (*data)->next;
		return (ft_strdup(s + i));
	}
	else
		return (get_back_fd_from_next_node(data, s));
}

void	add_exec_redir(t_exec *head, t_tok_list **data)
{
	t_redirect	*temp;

	if (head->redir == NULL)
	{
		head->redir = ft_new_redir();
		head->redir->front_fd = get_front_fd((*data)->str);
		head->redir->type = get_type_redir((*data)->str);
		head->redir->back_fd = get_back_fd(data);
	}
	else
	{
		temp = head->redir;
		while (temp->next)
			temp = temp->next;
		temp->next = ft_new_redir();
		temp->next->front_fd = get_front_fd((*data)->str);
		temp->next->type = get_type_redir((*data)->str);
		temp->next->back_fd = get_back_fd(data);
	}
}

void	ft_new_list_addback(t_list **head, char *s)
{
	t_list	*temp;

	if (*head == NULL)
	{
		*head = malloc(sizeof(t_list));
		temp = *head;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = malloc(sizeof(t_list));
		temp = temp->next;
	}
	temp->s = ft_strdup(s);
	temp->next = NULL;
}

int	get_condition(char *data)
{
	if (ft_strcmp(data, "||") == 0)
		return (OP_OR);
	if (ft_strcmp(data, "&&") == 0)
		return (OP_AND);
	if (ft_strcmp(data, "|") == 0)
		return (PIPE);
	return (0);
}
