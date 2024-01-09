/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeve_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:07:12 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 11:26:00 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_check_placeholder(int *checker, bool *in_s_quote,
		bool *in_d_quote)
{
	*in_s_quote = false;
	*in_d_quote = false;
	checker[0] = 0;
	checker[1] = 0;
}

void	check_for_placeholder(int *checker, char *str)
{
	bool	in_s_quote;
	bool	in_d_quote;

	setup_check_placeholder(checker, &in_s_quote, &in_d_quote);
	if (*str == '$')
		checker[0] = 1;
	while (*str)
	{
		if (ft_strchr("\'\"", *str))
		{
			if (*str == '\"' && in_s_quote == false)
				in_d_quote = !in_d_quote;
			else if (*str == '\'' && in_d_quote == false)
				in_s_quote = !in_s_quote;
			if (in_d_quote)
			{
				checker[1] = 1;
				return ;
			}
		}
		str++;
	}
}

int	manage_redir(t_exec *data, int *status, t_map_list *env)
{
	if (data->redir)
	{
		*status = run_redir(data, env, *status, 0);
		if (*status != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	ft_free_chrarr_with_ptr(char **arr)
{
	ft_free_chrarr(arr);
	free(arr);
}

int	no_cmd_to_run(int *checker, int *status, char **cmd)
{
	(void)cmd;
	if (checker[0] && checker[1] == 0)
	{
		*status = 0;
		return (0);
	}
	write(2, "minishell: : command not found\n", 31);
	*status = 127;
	return (127);
}
