/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 19:52:13 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/04 13:33:07 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int target)
{
	size_t	i;

	i = 0;
	target = (unsigned char)target;
	i = ft_strlen(s);
	while (i)
	{
		if (*(s + i) == target)
			return ((char *)(s + i));
		i--;
	}
	if (*(s + i) == target)
		return ((char *)(s + i));
	return (NULL);
}
