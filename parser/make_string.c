/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:53:39 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 00:03:30 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ---------------- make string -----------

int	ft_is_space(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

void	manage_string_helper(int *token, int *quote_indicate, int chr)
{
	if (*quote_indicate == 0)
	{
		*quote_indicate = 1;
		*token = chr;
	}
	else if (*quote_indicate == 1 && *token == chr)
	{
		*quote_indicate = 0;
		*token = 0;
	}
}

int	manage_string_space_return(int quote)
{
	if (quote != 0)
	{
		write(2, "minishell : syntax error near unexpected token `", 48);
		write(2, "newline`\n", 9);
		return (1);
	}
	return (0);
}

char	*manage_string_space_return_enc(char **src, int quote, char **res)
{
	if (*src)
		free(*src);
	*src = NULL;
	if (manage_string_space_return(quote))
	{
		if (*res)
			free(*res);
		*res = NULL;
		return (NULL);
	}
	return (*res);
}

char	*manage_string_space(char *src)
{
	int		i;
	int		quote;
	char	*res;
	int		token;

	i = 0;
	quote = 0;
	res = (char *)ft_calloc(ft_strlen(src) + 1, 1);
	while (src[i])
	{
		if (ft_strchr("\'\"", src[i]))
			manage_string_helper(&token, &quote, src[i]);
		if (ft_is_space(src[i]) && quote == 0)
			res[i] = ' ';
		else
			res[i] = src[i];
		i++;
	}
	return (manage_string_space_return_enc(&src, quote, &res));
}
