/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_if.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:27:32 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/03 14:27:34 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//condition == 0 still can run;
//condition == 1 move to next loop;
//condition == 2 break loop;

int	if_space(char *src, int *condition)
{
	if (*condition == 1)
		return (1);
	if (ft_is_space(*src))
	{
		*condition = 2;
		return (2);
	}
	return (0);
}

void	if_meet_quote(char **src, char **ptr, int *token, int *condition)
{
	recursive_token_quote_helper(src, ptr, token);
	*condition = 1;
}

int	if_meet_redir(char **src, char **ptr, int *token, char **buf)
{
	if (**buf == 0 || ft_strnum(*buf))
		recursive_token_redir_helper(src, ptr, token);
	if (ft_strchr("\"\'", **src) == 0)
		return (2);
	src[0] -= 1;
	return (1);
}

int	if_meet_paren(char **src, int *token, t_tok_list **branch, char **buf)
{
	if (**src == ')')
		src[0] += 1;
	else if (**buf == 0)
		recursive_token_paren_helper(src, token, &(*branch)->child);
	return (2);
}

int	if_meet_condition(char **src, char **ptr, int *token, char **buf)
{
	if (**buf == 0)
	{
		recursive_token_cond_helper(src, ptr, token);
		if (*token)
			return (2);
		src--;
		return (1);
	}
	return (2);
}
