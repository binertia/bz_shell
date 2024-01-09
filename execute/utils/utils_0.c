/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:18:01 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:41:14 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_exec	*make_new_exec(void)
{
	t_exec	*new;

	new = (t_exec *)malloc(sizeof(t_exec));
	new->run_condition = 0;
	new->child = NULL;
	new->cmd = NULL;
	new->redir = NULL;
	new->next = NULL;
	return (new);
}

int	get_type_size(int type, t_tok_list *data)
{
	int	res;

	res = 0;
	while (data && data->token != PARENT_TYPE)
	{
		if (data->token == type)
			res++;
		data = data->next;
	}
	return (res);
}

void	add_exec_args(t_exec *head, t_tok_list *data, int type)
{
	t_redirect	*temp;

	(void)data;
	(void)type;
	temp = head->redir;
	while (temp->next)
		temp = temp->next;
}

t_redirect	*ft_new_redir(void)
{
	t_redirect	*new;

	new = malloc(sizeof(t_redirect));
	new->type = 0;
	new->front_fd = NULL;
	new->back_fd = NULL;
	new->next = NULL;
	new->heredoc = NULL;
	return (new);
}

int	ft_atoi_strict(char *s)
{
	int	res;

	res = 0;
	while (*s)
	{
		if (*s > '9' || *s < '0')
			return (-1);
		res = (res * 10) + (*s++ - '0');
	}
	return (res);
}
