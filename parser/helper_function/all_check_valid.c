/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_check_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:40:24 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 12:01:26 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_paren_valid_error(char *str)
{
	write(2, "minishell : syntax error unexpected token at ", 45);
	write(2, "`", 1);
	if (ft_strchr(str, ')'))
		write(2, ")", 1);
	else
		write(2, "newline", 7);
	write(2, "`\n", 2);
	return (0);
}

void	check_paren_valid_in_quote(char **src_str, int *token)
{
	*token = src_str[0][0];
	src_str[0] += 1;
	while (src_str[0] && src_str[0][0] != *token)
		src_str[0] += 1;
	if (src_str[0][0] == 0)
		src_str[0] -= 1;
}

int	check_paren_valid(char *str)
{
	int	count;
	int	token;

	count = 0;
	while (*str)
	{
		if (*str == '(')
			count++;
		else if (*str == ')')
			count--;
		else if (ft_strchr("\'\"", *str))
			check_paren_valid_in_quote(&str, &token);
		if (count < 0)
			break ;
		str++;
	}
	if (count == 0)
		return (1);
	return (check_paren_valid_error(str));
}
