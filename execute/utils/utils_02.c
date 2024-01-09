/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:15:42 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/06 09:16:00 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tok_list	*ft_toklist_last(t_tok_list *head)
{
	if (head == NULL)
		return (NULL);
	else
	{
		while (head->next)
			head = head->next;
		return (head);
	}
}

t_tok_list	*ft_toklist_addlast(t_tok_list *head)
{
	if (head == NULL)
		head = ft_new_toklist();
	else
	{
		while (head->next)
			head = head->next;
		head->next = ft_new_toklist();
	}
}
