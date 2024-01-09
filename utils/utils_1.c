/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:08:05 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/09 13:04:02 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	loop_add_buffer(char *str, int i, t_list **res)
{
	char	*temp;

	temp = ft_strndup(str, i);
	ft_new_list_addback(res, temp);
	free(temp);
	temp = NULL;
}

void	loop_add_replace(t_list **res, char *temp, char **str, size_t *i)
{
	if (temp)
	{
		ft_new_list_addback(res, temp);
		free(temp);
		temp = NULL;
	}
	*str = *str + *i;
	*i = 0;
}

t_list	*add_last_buf(char *str, int i, t_list **res)
{
	char	*temp;

	if (i)
	{
		temp = ft_strdup(str);
		ft_new_list_addback(res, temp);
		free(temp);
		temp = NULL;
	}
	return (*res);
}

void	setup_get_replaced(t_list **res, size_t *i, bool *in_s_quote,
		bool *in_d_quote)
{
	*i = 0;
	*res = NULL;
	*in_s_quote = false;
	*in_d_quote = false;
}

t_list	*get_replaced(char *str, t_map_list *env, int status)
{
	t_list	*res;
	size_t	i;
	char	*temp;
	bool	in_s_quote;
	bool	in_d_quote;

	temp = NULL;
	setup_get_replaced(&res, &i, &in_s_quote, &in_d_quote);
	while (str[i])
	{
		if (str[i] == '\'' && in_d_quote == false && i++ > -1)
			in_s_quote = !in_s_quote;
		else if (str[i] == '\"' && in_s_quote == false && i++ > -1)
			in_d_quote = !in_d_quote;
		else if (str[i] == '$' && str[i + 1] && ft_is_space(str[i + 1]) \
				== 0 && ft_strchr("\"\'=()", str[i + 1]) == 0 \
				&& in_s_quote == false)
		{
			loop_add_buffer(str, i, &res);
			temp = replace_addback(str, &i, env, status);
			loop_add_replace(&res, temp, &str, &i);
		}
		else
			i++;
	}
	return (add_last_buf(str, i, &res));
}
