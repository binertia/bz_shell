/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:49:37 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 18:25:05 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	setup_search_replace(bool *s_quote, bool *d_quote, size_t *i)
{
	*s_quote = false;
	*d_quote = false;
	*i = 0;
}

t_list	*get_heredoc_replaced(char *str, t_map_list *env, int status)
{
	t_list	*res;
	size_t	i;
	char	*temp;

	i = 0;
	res = NULL;
	i = loop_search_replace(&str, env, status, &res);
	if (i)
	{
		temp = ft_strdup(str);
		ft_new_list_addback(&res, temp);
		free(temp);
	}
	return (res);
}

int	setup_replace_hered_str(char **str, t_map_list *env, int status,
		t_list **head)
{
	if (*str == 0 || **str == 0 || is_parse_able(*str) == 0)
		return (1);
	*head = get_heredoc_replaced(*str, env, status);
	if (*head == NULL)
		return (1);
	return (0);
}

void	ft_replace_hered_set_free(char **str, t_list *for_free, char *res)
{
	ft_free_list(for_free);
	free(*str);
	*str = res;
}
