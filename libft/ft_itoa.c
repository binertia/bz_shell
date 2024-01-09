/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:01:46 by spipitku          #+#    #+#             */
/*   Updated: 2023/08/29 11:06:23 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*zero(void)
{
	char	*ptr;

	ptr = malloc(2);
	if (ptr == NULL)
		return (ptr);
	ptr[0] = '0';
	ptr[1] = '\0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		first_n;
	int		count;
	char	*ptr;

	count = 0;
	first_n = n;
	if (n == 0)
		return (zero());
	if (n < 0)
		n = -n;
	count = count_alpha_of_num_in_n(n);
	if (first_n < 0)
	{
		ptr = malloc(count + 1 + 1);
		if (!ptr)
			return (ptr);
		ptr[count + 1] = '\0';
	}
	else
	{
		ptr = malloc(count + 1);
		ptr[count] = '\0';
	}
	number_put_in_to_ptr(&ptr, count, first_n);
	return (ptr);
}

int	count_alpha_of_num_in_n(int n)
{
	int	count;

	count = 0;
	while (n > 0 || n < 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

void	number_put_in_to_ptr(char **ptr_main, int count, int sum)
{
	char	*ptr;

	ptr = *ptr_main;
	if (sum == -2147483648)
	{
		ptr[0] = '-';
		ptr[1] = '2';
		sum = 147483648;
		count++;
	}
	else if (sum < 0)
	{
		sum = -sum;
		ptr[0] = '-';
		count++;
	}
	while (sum > 0)
	{
		count--;
		ptr[count] = (sum % 10) + '0';
		sum = sum / 10;
	}
}
