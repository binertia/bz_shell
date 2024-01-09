/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:49:39 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/04 13:32:59 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	find_word(const char *big, const char *little, size_t i, size_t len)
{
	size_t		j;
	size_t		clone_i;

	clone_i = i;
	j = 0;
	while ((*(big + clone_i) == *(little + j)) && *(little + j) && \
			*(big + clone_i) && clone_i < len)
	{
		clone_i++;
		j++;
	}
	return (j);
}

size_t	send_string(const char *big, const char *little, size_t len, \
		size_t *i_main)
	{
	size_t	j;
	size_t	i;
	size_t	clone_len;

	clone_len = len;
	i = 0;
	j = 0;
	while (len-- && *(big + i))
	{
		if (*(big + i) == *(little + j))
			j = find_word(big, little, i, clone_len);
		if (j == ft_strlen(little))
		{
			*i_main = i;
			return (1);
		}
		j = 0;
		i++;
	}
	return (j);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!big && little && !len)
		return ((char *)(big + 1));
	if (!big && !little && !len)
		return (NULL);
	if (!ft_strlen(big) && ft_strlen(little))
		return (NULL);
	else if (!ft_strlen(little))
		return ((char *)big);
	if (len && send_string(big, little, len, &i))
		return ((char *)(big + i));
	return (0);
}
