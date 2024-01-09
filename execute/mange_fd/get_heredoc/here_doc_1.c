/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:44:50 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 18:01:50 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	replace_addback_manage(char *str, size_t *i, bool *in_quote)
{
	if (str[*i] == '\'' && in_quote[1] == false && *i++ != (size_t)-1)
	{
		*i += 1;
		in_quote[0] = !in_quote[0];
	}
	else if (str[*i] == '\"' && in_quote[0] == false && *i != (size_t)-1)
	{
		*i += 1;
		in_quote[1] = !in_quote[1];
	}
}

void	update_and_free(t_list **res, char **temp, char **str, size_t *i)
{
	ft_new_list_addback(res, *temp);
	if (*temp)
		free(*temp);
	*temp = NULL;
	str[0] += *i;
	*i = 0;
}

void	loop_search_temp_condition(char **temp, t_list **res)
{
	if (*temp)
	{
		ft_new_list_addback(res, *temp);
		if (*temp)
			free(*temp);
		*temp = NULL;
	}
}

int	loop_search_replace(char **str, t_map_list *env, int status, t_list **res)
{
	bool	in_quote[2];
	size_t	i;
	char	*temp;

	setup_search_replace(&in_quote[0], &in_quote[1], &i);
	while (str[0][i])
	{
		if ((str[0][i] == '\'' && in_quote[1] == false && i++ != \
			(size_t)(-1)) || (str[0][i] == '\"' && \
			in_quote[0] == false && i++ != (size_t)(-1)))
			replace_addback_manage(*str, &i, in_quote);
		else if (str[0][i] == '$' && str[0][i + 1] && ft_is_space(str[0][i
					+ 1]) == 0 &&
					ft_strchr("\"\'=()", str[0][i + 1]) == 0)
		{
			temp = ft_strndup(*str, i);
			loop_search_temp_condition(&temp, res);
			temp = replace_addback(*str, &i, env, status);
			update_and_free(res, &temp, str, &i);
		}
		else
			i++;
	}
	return (i);
}
