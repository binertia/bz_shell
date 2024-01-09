/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_quote_and_recursive_token.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:41:54 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 18:54:03 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// ------------------ helper function ------------
int	valid_quote(char *str)
{
	int		token;
	char	*temp;

	temp = str;
	token = *str;
	str++;
	while (*str && *str != token)
		str++;
	if (*str == token)
		return (str - temp);
	return (0);
}

void	recursive_token_quote_helper(char **src, char **ptr, int *type)
{
	int	token;

	(void)type;
	token = **src;
	**ptr = **src;
	*src += 1;
	*ptr += 1;
	while (**src && **src != token)
	{
		**ptr = **src;
		*ptr += 1;
		*src += 1;
	}
	**ptr = **src;
	*ptr += 1;
}

void	recursive_token_redir_add_char(char **src, int chr_buf, char **buf_ptr,
		int *count)
{
	(void)count;
	while (**src == chr_buf)
	{
		**buf_ptr = **src;
		*buf_ptr += 1;
		*src += 1;
		count++;
	}
}

void	recursive_token_redir_helper(char **src, char **buf_ptr, int *token)
{
	int	count;
	int	chr_buf;

	count = 0;
	*token = REDIR_TYPE;
	chr_buf = **src;
	recursive_token_redir_add_char(src, chr_buf, buf_ptr, &count);
	if (count > 2)
		*token = ERROR_TYPE;
	if (**src == '&')
	{
		if (*(*src + 1) && *(*src + 1) == '&')
		{
			src--;
			return ;
		}
	}
	while (**src && ft_strchr("|<>()\'\" ", **src) == NULL && \
			ft_is_space(**src) == 0)
	{
		**buf_ptr = **src;
		*buf_ptr += 1;
		*src += 1;
	}
}

void	recursive_token_cond_helper(char **src, char **ptr, int *token)
{
	int		buf_token;

	buf_token = **src;
	*token = CONDITION_TYPE;
	if (**src == '&' && *(*src + 1) && *(*src + 1) != '&')
	{
		**ptr = **src;
		*ptr += 1;
		*token = ARGS_TYPE;
		return ;
	}
	while (**src && **src == buf_token)
	{
		**ptr = **src;
		*ptr += 1;
		*src += 1;
	}
}
