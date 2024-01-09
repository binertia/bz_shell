/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:50:50 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/07 19:25:55 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	t_map_list	*env;
	char		*hidden_pwd;

	(void)ac;
	(void)av;
	env = get_env_list(envp);
	hidden_pwd = set_hidden_fallback_pwd();
	if (hidden_pwd == NULL)
		return (no_sufficient_data_to_run());
	set_hidden(env, hidden_pwd);
	setup(env);
	print_header(env);
	return (minishell(env));
}
