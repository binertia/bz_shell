/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:10:37 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/04 13:33:17 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	find_end(char const *s1, char const *set)
{
	size_t	end;

	end = ft_strlen(s1) - 1;
	while (s1[end])
	{
		if (ft_strchr(set, s1[end]))
			end--;
		else
			break ;
	}
	return (end);
}

size_t	find_start(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1[start])
	{
		if (ft_strchr(set, s1[start]))
			start++;
		else
			break ;
	}
	return (start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)(s1));
	start = 0;
	end = ft_strlen(s1) - 1;
	start = find_start(s1, set);
	if (start - end == 1)
		return (ft_strdup(""));
	end = find_end(s1, set);
	ptr = ft_substr(s1, start, end - start + 1);
	return (ptr);
}
