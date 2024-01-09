/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:04:27 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/09 11:42:55 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *s, t_map_list *env, int status)
{
	if (ft_strcmp(s, "$") == 0)
		return (i_hope_i_can_use_getpid());
	else if (ft_strcmp(s, "?") == 0)
		return (ft_itoa(status));
	else if (ft_strcmp(s, "0") == 0)
		return (ft_strdup("minishell"));
	while (env)
	{
		if (ft_strcmp(env->key, s) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_calloc(1, 1));
}

int	ft_strnum_only(char *s)
{
	if (s == NULL || *s == 0)
		return (0);
	while (*s && *s >= '0' && *s <= '9')
		s++;
	if (*s)
		return (0);
	return (1);
}

void	setup_replace_addback(char *str, size_t *index, char **buf, char **ptr)
{
	*index += 1;
	// *buf = ft_calloc(ft_strlen(str + *index) + 1, 1);
	*buf = ft_calloc(ft_strlen(str) + 1, 1);
	*ptr = *buf;
}

char	*replace_addback_return(char **buf, t_map_list *env, int status)
{
	char	*temp;

	temp = ft_getenv(*buf, env, status);
	free(*buf);
	*buf = NULL;
	return (temp);
}

char	*replace_addback(char *str, size_t *index, t_map_list *env, int status)
{
	char	*buf;
	char	*ptr;
	int		count;

	count = 0;
	setup_replace_addback(str, index, &buf, &ptr);
	while (str[*index] && ft_strchr("\"\'", str[*index]) == 0 && \
		ft_is_space(str[*index]) == 0 && ft_strchr("()=", str[*index]) == 0)
	{
		if (str[*index] == '$' && count > 0)
			break ;
		count++;
		*ptr++ = str[*index];
		*index += 1;
		if (ptr - buf < 2)
		{
			if (ft_strcmp(buf, "$") == 0 || ft_strcmp(buf, "?") == 0 || \
				ft_strnum_only(buf))
				break ;
		}
	}
	if (str[*index] && ft_strchr("\'\"=()", str[*index]))
		*ptr = 0;
	return (replace_addback_return(&buf, env, status));
}
