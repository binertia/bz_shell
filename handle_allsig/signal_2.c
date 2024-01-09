/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spipitku <spipitku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:33:14 by spipitku          #+#    #+#             */
/*   Updated: 2024/01/09 10:05:04 by spipitku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	sigint_handler(int signum)
// {
// 	if (signum == SIGINT)
// 	{
// 		printf("heredoc>\n");
// 		g_sigint_in = 1;
// 		exit(EXIT_FAILURE);
// 	}
// }

// ---- choose which one tmr
// void	new_sigint_handler(int signum, siginfo_t *info, void *ptr)
// {
// 	(void)info;
// 	(void)ptr;
// 	if (signum == SIGINT)
// 	{
// 		printf("\n");
// 		g_sigint_in = 1;
// 	}
// }

// void	sig_setup_heredoc(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_sigaction = sigint_handler;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_SIGINFO;
// 	sa.sa_flags |= SA_RESTART;
// 	sigaction(SIGINT, &sa, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	sig_hered(int signal)
{
	install_term();
	if (signal == SIGINT)
	{
		printf("\n");
		exit(1);
	}
	else if (signal == SIGQUIT)
		return ;
}

void	mod_sig_handle(void (*fn)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = fn;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT,SIG_IGN);
}
