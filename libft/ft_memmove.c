/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:14:43 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/06 15:22:47 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *to, const void *from, size_t numBytes)
{
	unsigned char	*dest;
	unsigned char	*src;

	dest = (unsigned char *)to;
	src = (unsigned char *)from;
	if (dest == src)
		return (to);
	if (to < from)
		return (ft_memcpy(to, from, numBytes));
	dest = dest + numBytes - 1;
	src = src + numBytes - 1;
	while (numBytes--)
		*dest-- = *src--;
	return (to);
}
