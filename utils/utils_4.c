/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:32:13 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 00:16:28 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup_str;

	len = ft_strnlen(s, n);
	dup_str = (char *)calloc(len + 1, 1);
	if (dup_str != NULL)
	{
		ft_memcpy(dup_str, s, len);
		dup_str[len] = '\0';
	}
	return (dup_str);
}

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	const char	*end;

	end = s;
	while (*end && maxlen > 0)
	{
		++end;
		--maxlen;
	}
	return ((size_t)(end - s));
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*hay;
	const char	*ned;

	while (*haystack)
	{
		hay = haystack;
		ned = needle;
		while (*hay && *ned && *hay == *ned)
		{
			hay++;
			ned++;
		}
		if (*ned == '\0')
		{
			return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
