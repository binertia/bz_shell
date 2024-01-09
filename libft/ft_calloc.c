/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:24:39 by spipitku          #+#    #+#             */
/*   Updated: 2023/09/02 17:07:15 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	p = (void *)malloc(nmemb * size);
	if (p == NULL)
		return (p);
	ft_bzero(p, nmemb * size);
	return (p);
}
