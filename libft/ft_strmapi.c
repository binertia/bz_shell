/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:42:16 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/04 13:32:04 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t		i;
	char		*ptr;
	size_t		member_in_s;

	i = 0;
	if (!s)
		return (NULL);
	member_in_s = ft_strlen(s);
	if (!(*s))
		return (ft_strdup(""));
	ptr = malloc(member_in_s + 1);
	if (!ptr)
		return (NULL);
	while (*s)
	{
		*(ptr + i) = (*f)(i, *s++);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
