/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:39:52 by spipitku          #+#    #+#             */
/*   Updated: 2023/08/26 19:40:28 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	i_copy;

	i_copy = 0;
	i = 0;
	while (src[i])
		i++;
	if (!(size))
		return (i);
	while (--size && src[i_copy])
	{
		dst[i_copy] = src[i_copy];
		i_copy++;
	}
	dst[i_copy] = '\0';
	return (i);
}
