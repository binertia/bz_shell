/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:45:43 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 16:09:13 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// int	setup_replace_hered_str(char **str, t_map_list *env, int status,
// 		t_list **head)
// {
// 	if (*str == 0 || **str == 0 || is_parse_able(*str) == 0)
// 		return (1);
// 	*head = get_heredoc_replaced(*str, env, status);
// 	if (*head == NULL)
// 		return (1);
// 	return (0);
// }

// void	ft_replace_hered_set_free(char **str, t_list *for_free, char *res)
// {
// 	ft_free_list(for_free);
// 	free(*str);
// 	*str = res;
// }

void	replace_hered_get_list_len(t_list *src, size_t *len)
{
	t_list	*temp;

	temp = src;
	while (temp)
	{
		if (temp->s && temp->s[0])
			*len += ft_strlen(temp->s);
		temp = temp->next;
	}
}

void	replace_hered_str(char **str, t_map_list *env, int status)
{
	t_list	*head;
	size_t	len;
	t_list	*for_free;
	char	*res;

	len = 0;
	if (setup_replace_hered_str(str, env, status, &head) == 1)
		return ;
	replace_hered_get_list_len(head, &len);
	res = ft_calloc(len + 1, 1);
	for_free = head;
	while (head)
	{
		if (head->s && head->s[0])
			ft_strcat(res, head->s);
		head = head->next;
	}
	ft_replace_hered_set_free(str, for_free, res);
}

int	check_parsing_eof(char **eof, t_redirect **temp, int *status,
		t_map_list *env)
{
	int	not_parse;

	not_parse = 0;
	if (ft_strchr(*eof, '\'') || ft_strchr(*eof, '\"'))
	{
		not_parse = 1;
		unquote_realloc_str(eof);
	}
	(*temp)->heredoc = add_heredoc(*eof, status);
	if (*eof)
	{
		free(*eof);
		*eof = NULL;
	}
	if (*status != 0)
		return (1);
	else if (not_parse == 0)
		replace_hered_str(&(*temp)->heredoc, env, *status);
	return (0);
}

void	get_eof_from_next_args(t_exec *list, char **eof)
{
	if (list->next == NULL || \
			list->cmd->s == NULL)
		exit(EXIT_FAILURE);
	else
		*eof = ft_strdup(list->cmd->s);
}

int	get_heredoc_loop(t_exec *exec_temp, int *status, t_map_list *env)
{
	t_redirect	*temp;
	char		*eof;

	temp = exec_temp->redir;
	while (temp)
	{
		if (temp->type == HERED)
		{
			if (temp->back_fd)
				eof = ft_strdup(temp->back_fd);
			else
				get_eof_from_next_args(exec_temp, &eof);
			if (check_parsing_eof(&eof, &temp, status, env) == 1)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}
