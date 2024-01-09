/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:13:31 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/04 13:33:33 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*zero(void)
{
	char	*ptr;

	ptr = malloc(1);
	ptr[0] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ptr;
	size_t		i;

	i = 0;
	if (!s && !start && !len)
		return (ft_strdup(""));
	if (!s)
		return (NULL);
	if (ft_strlen(s) == 0 || start > ft_strlen(s))
		return (zero());
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (len--)
		ptr[i++] = s[start++];
	ptr[i] = '\0';
	return (ptr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s",ft_substr("",0,0));
// }
