/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:37:56 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/06 11:53:44 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hook_sigint(t_exec **head, t_map_list **env)
{
	if (*head)
	{
		ft_free_exec(*head);
		*head = NULL;
	}
	if (*env)
	{
		ft_free_map_list(*env);
		*env = NULL;
	}
}

int	hook_eof(char *input)
{
	printf("%sexit\n", PROMPT_MSG);
	if (input)
		free(input);
	input = NULL;
	return (1);
}
