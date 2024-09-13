/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:52:13 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/13 16:09:14 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

// void	sigint_handler_wait(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		write(0, "\n", 1);
// 		// rl_replace_line("", 0);
// 		// rl_on_new_line();
// 		// rl_redisplay();
// 	}
// }

// void	sigint_handler_hd(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		write(0, "\n", 1);
// 		close(0);
// 		g_sig = 130;
// 	}
// }

void	sigint_handler_prompt(int signal)
{
	if (signal == SIGINT)
	{
		write(0, "\n", 1);
		rl_replace_line("\0", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig = 130;
	}
}

void	set_signal_action(int a)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	signal(SIGQUIT, SIG_IGN);
	if (!a)
	{
		act.sa_handler = &sigint_handler_prompt;
		sigaction(SIGINT, &act, NULL);
	}
	// else if (a == 1)
	// {
	// 	act.sa_handler = &sigint_handler_hd;
	// 	sigaction(SIGINT, &act, NULL);
	// }
	// else if (a == 2)
	// 	signal(SIGINT, SIG_DFL);
	// else if (a == 3)
	// {
	// 	act.sa_handler = &sigint_handler_wait;
	// 	sigaction(SIGINT, &act, NULL);
	// }
	// else if (a == 4)
	// 	signal(SIGINT, SIG_IGN);
}
