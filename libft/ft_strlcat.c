/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 14:35:50 by spipitku          #+#    #+#             */
/*   Updated: 2023/08/29 08:42:02 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((!dest && !src))
		return (0);
	if (!size)
		return (ft_strlen(src));
	while (*dest && i < size)
	{
		dest++;
		i++;
	}
	if (i == size)
		return (i + ft_strlen(src));
	while (src[j])
	{
		if (j < size - i - 1)
			*dest++ = src[j];
		j++;
	}
	*dest = '\0';
	return (i + j);
}
