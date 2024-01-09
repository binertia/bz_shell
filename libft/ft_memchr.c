/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:55:03 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/06 15:20:54 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t n)
{
	size_t				i;
	const unsigned char	*p;

	i = 0;
	p = (const unsigned char *)ptr;
	value = (unsigned char)value;
	while (i < n)
	{
		if (p[i] == value)
			return ((void *)(p + i));
		i++;
	}
	return (NULL);
}
