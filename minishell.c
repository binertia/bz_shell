/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:23:28 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:20:58 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_null(t_exec **head, char **input)
{
	*head = NULL;
	*input = NULL;
}

int	minishell(t_map_list *env)
{
	int				g_status;
	char			*input;
	t_exec			*head;

	head = NULL;
	g_status = 0;
	while (g_status < 500)
	{
		mod_sig_handle(sig_handler);
		input = readline(PROMPT_MSG);
		child_ignore();
		if (!input && hook_eof(input))
			break ;
		else if (*input == '\n')
			printf("\n");
		else if (input && input[0])
			set_add_history(input, &env, &g_status, &head);
		clean_unused_cmd(&head, &input);
	}
	hook_sigint(&head, &env);
	return ((unsigned char)g_status);
}

void	ft_stack_std(int *arr)
{
	arr[0] = dup(STDIN_FILENO);
	arr[1] = dup(STDOUT_FILENO);
	arr[2] = dup(STDERR_FILENO);
}

int	run_line(char *raw_data, t_map_list **env, int *g_status, t_exec **cmd)
{
	int	std[3];

	ft_stack_std(std);
	*cmd = parser(raw_data, *env, g_status);
	if (*cmd == NULL)
	{
		if (*g_status != 1)
			*g_status = 258;
		ft_fflush(std, 0, 1, 0);
		return (*g_status);
	}
	execute_recursive(*cmd, g_status, env, 0);
	ft_fflush(std, 1, 1, 1);
	return (*g_status);
}
