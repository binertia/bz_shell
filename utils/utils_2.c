/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:17:45 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 17:46:12 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_unqoute_string(t_unquote_string *norm)
{
	norm->i = 0;
	norm->j = 0;
	norm->in_double_quote = 0;
	norm->in_single_quote = 0;
}

char	*unquote_string(char *input)
{
	struct s_unquote_string	norm;

	setup_unqoute_string(&norm);
	if (input == NULL)
		return (NULL);
	norm.len = ft_strlen(input);
	norm.output = ft_calloc((norm.len + 1), 1);
	if (norm.output == NULL)
		return (NULL);
	while (norm.i < norm.len)
	{
		if (input[norm.i] == '\"' && !norm.in_single_quote)
			norm.in_double_quote = !norm.in_double_quote;
		else if (input[norm.i] == '\'' && !norm.in_double_quote)
			norm.in_single_quote = !norm.in_single_quote;
		else
			norm.output[norm.j++] = input[norm.i];
		norm.i++;
	}
	norm.output[norm.j] = 0;
	return (norm.output);
}

void	unquote_realloc_str(char **str)
{
	char	*str_temp;

	if (*str && **str && (ft_strchr(*str, '\"') || ft_strchr(*str, '\'')))
	{
		str_temp = unquote_string(*str);
		free(*str);
		*str = str_temp;
	}
	return ;
}

void	ft_free_list(t_list *head)
{
	if (head == NULL)
		return ;
	if (head->next)
	{
		ft_free_list(head->next);
		head->next = NULL;
	}
	if (head->s)
	{
		free(head->s);
		head->s = NULL;
	}
	free(head);
}

void	replace_str_moving_ptr(t_list **temp, size_t *len)
{
	if ((*temp)->s && (*temp)->s[0])
		*len += ft_strlen((*temp)->s);
	(*temp) = (*temp)->next;
}
