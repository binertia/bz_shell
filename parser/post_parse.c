/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:59:19 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:17:00 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	setup_is_parse_able(int *status, bool *in_s_quote, bool *in_d_quote,
		char *s)
{
	*status = 0;
	*in_s_quote = false;
	*in_d_quote = false;
	if (s[1] && s[1] == '=')
		return (0);
	return (1);
}

int	is_parse_able(char *s)
{
	int		status;
	bool	in_s_quote;
	bool	in_d_quote;

	if (setup_is_parse_able(&status, &in_s_quote, &in_d_quote, s) == 0)
		return (0);
	while (*s)
	{
		if (*s == '\"' && in_s_quote == false)
			in_d_quote = !in_d_quote;
		else if (*s == '\'' && in_d_quote == false)
			in_s_quote = !in_s_quote;
		else if (*s == '$' && in_s_quote == false)
		{
			if (*s && s[1] && ft_strchr("\'\"", s[1]) == 0)
				status = 1;
		}
		s++;
	}
	if (status)
		return (1);
	return (0);
}

char	*i_hope_i_can_use_getpid(void)
{
	int	d;

	d = 69;
	if (8 == d)
	{
		printf("thanks for read me\n");
		return (NULL);
	}
	else
		return (ft_strdup("<SUPPOSE TO BE PID>"));
}
