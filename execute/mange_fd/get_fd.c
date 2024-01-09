/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:34:51 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/04 11:49:39 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_front_fd(char *s)
{
	char	*buf;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	buf = NULL;
	while (!(*(s + i) == '>' || *(s + i) == '<'))
		i++;
	if (i != 0)
	{
		buf = ft_calloc(i + 1, 1);
		while (j < i)
		{
			buf[j] = s[j];
			j++;
		}
	}
	return (buf);
}

int	get_type_redir_case(char *s, int i)
{
	if (s[i] == '>')
	{
		if (s[i + 1] && s[i + 1] == '>')
			return (APPEN);
		else if (s[i + 2] && s[i + 2] == '>')
			return (REDIR_ERR);
		else
			return (O_REDIR);
	}
	else if (s[i] == '<')
	{
		if (s[i + 1] && s[i + 1] == '<')
		{
			return (HERED);
		}
		else if (s[i + 2] && s[i + 2] == '>')
			return (REDIR_ERR);
		else
			return (I_REDIR);
	}
	return (0);
}

int	get_type_redir(char *s)
{
	int	i;

	i = 0;
	while (ft_strchr("><", s[i]) == NULL)
		i++;
	if (s[i] == '>' || s[i] == '<')
		return (get_type_redir_case(s, i));
	return (-1);
}

int	valid_numb_str(char *s)
{
	if (*s == 0)
		return (-1);
	while (*s >= '0' && *s <= '9')
		s++;
	if (*s)
		return (0);
	return (1);
}

char	*get_back_fd_from_next_node(t_tok_list **data, char *s)
{
	*data = (*data)->next;
	if (*data == NULL)
		return (NULL);
	if ((*data)->token != ARGS_TYPE)
		return (NULL);
	else
	{
		s = (*data)->str;
		*data = (*data)->next;
		return (ft_strdup(s));
	}
}
