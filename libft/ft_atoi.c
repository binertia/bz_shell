/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:36:56 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 17:47:02 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	found_9_to_13(const char *str)
{
	int	i;

	i = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	return (i);
}

int	check_plus_or_neg(int *sum, int i, const char *str)
{
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sum = *sum * (-1);
		i++;
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sum;
	int	sum_ans;

	sum_ans = 0;
	sum = 1;
	i = found_9_to_13(str);
	i = check_plus_or_neg(&sum, i, str);
	while (str[i] >= '0' && str[i] <= '9')
		sum_ans = sum_ans * 10 + (str[i++] - '0');
	return (sum_ans * sum);
}

// #include <stdio.h>
// int	main(void)
// {
// 	printf("%d",ft_atoi("++7-9"));
// }
