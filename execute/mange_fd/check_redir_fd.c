/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:31:34 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 16:43:52 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_redir(char **str, int *count, int *redir)
{
	*redir = **str;
	while (**str == *redir)
	{
		*count += 1;
		*str += 1;
	}
}

int	check_redir_valid(char *str)
{
	int	count;
	int	token;
	int	redir;

	count = 0;
	while (*str)
	{
		if (*str == '>' || *str == '<')
		{
			skip_redir(&str, &count, &redir);
			if (count > 2)
				return (check_redir_valid_error(redir));
			if (check_child(str) == 0)
				return (0);
			str--;
			count = 0;
		}
		else if (ft_strchr("\'\"", *str))
			move_ptr_in_quote(&token, &str);
		if (count < 0)
			break ;
		str++;
	}
	return (1);
}

int	check_redir_valid_error(int redir)
{
	write(2, "minishell : syntax error unexpected token at `", 46);
	write(2, &redir, 1);
	write(2, "`\n", 2);
	return (0);
}

void	move_ptr_in_quote(int *token, char **str)
{
	*token = **str;
	*str += 1;
	while (**str && **str != *token)
		*str += 1;
	if (*str == 0)
		*str -= 1;
}
