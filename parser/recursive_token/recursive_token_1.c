/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_token_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:21:24 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 17:43:12 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_recursive_token(char *src, char **buf, char **ptr,
		t_tok_list **branch)
{
	*buf = ft_calloc(ft_strlen(src) + 1, 1);
	*branch = ft_new_toklist();
	*ptr = *buf;
}

int	recursive_token_skip_space(char **src, int *utils)
{
	utils[0] = 0;
	utils[1] = 0;
	while (**src && ft_is_space(**src))
		src[0] += 1;
	if (**src == 0)
		return (0);
	return (1);
}

void	recursive_token_send_next(char **src, char **buf, int *token,
		t_tok_list **branch)
{
	add_list_data(buf, *token, *branch);
	if (src && *src != 0)
		recursive_token(*src, &(*branch)->next, 0, 0);
}

int	recursive_token_setup_loop(char **src, int *condition)
{
	if (*condition == 2)
		return (0);
	*condition = 0;
	src[0] += 1;
	return (1);
}

void	recursive_token(char *src, t_tok_list **branch, int root_call,
		char *temp)
{
	t_recursive_token	n;

	setup_void(temp, root_call);
	if (recursive_token_skip_space(&src, n.utils) == 0)
		return ;
	setup_recursive_token(src, &n.buf, &n.ptr, branch);
	while (*src)
	{
		if (if_space(src, &n.utils[0]) == 2)
			break ;
		else if (n.utils[0] == 0 && ft_strchr("\"\'", *src))
			if_meet_quote(&src, &n.ptr, &n.utils[1], &n.utils[0]);
		else if (n.utils[0] == 0 && ft_strchr("<>", *src))
			n.utils[0] = if_meet_redir(&src, &n.ptr, &n.utils[1], &n.buf);
		else if (n.utils[0] == 0 && ft_strchr("|&", *src))
			n.utils[0] = if_meet_condition(&src, &n.ptr, &n.utils[1], &n.buf);
		else if (n.utils[0] == 0 && ft_strchr("()", *src))
			n.utils[0] = if_meet_paren(&src, &n.utils[1], branch, &n.buf);
		else if (n.utils[0] == 0)
			*n.ptr++ = *src;
		if (recursive_token_setup_loop(&src, &n.utils[0]) == 0)
			break ;
	}
	recursive_token_send_next(&src, &n.buf, &(n.utils[1]), branch);
}
