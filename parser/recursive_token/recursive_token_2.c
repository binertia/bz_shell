/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_token_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:21:39 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 00:05:57 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	recursive_token_paren_setup(int *token, int *count, \
		char **src, char **buf)
{
	*token = PARENT_TYPE;
	*count = 1;
	*src += 1;
	*buf = ft_calloc(ft_strlen(*src) + 1, 1);
}

void	recursive_token_paren_helper(char **src, int *token, t_tok_list **list)
{
	char	*buf;
	char	*buf_ptr;
	int		count;
	char	*temp;

	recursive_token_paren_setup(token, &count, src, &buf);
	buf_ptr = buf;
	temp = buf;
	while (**src && count != 0)
	{
		*buf_ptr = **src;
		if (**src == '(')
			count++;
		else if (**src == ')')
			count--;
		if (count != 0)
			buf_ptr += 1;
		else
			*buf_ptr = 0;
		*src += 1;
	}
	recursive_token(buf, list, 0, 0);
	free(temp);
}

void	add_list_data(char **s, int token, t_tok_list *list)
{
	list->str = *s;
	list->token = token;
}
