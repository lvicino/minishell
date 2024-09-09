/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:52:13 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/09 16:53:31 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	sigint_handler_exec(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_sig = 130;
	}
}

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig = 130;
	}
}

void	set_signal_action(int a)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	if (a)
	{
		act.sa_handler = &sigint_handler;
		sigaction(SIGINT, &act, NULL);
	}
	else
	{
		act.sa_handler = &sigint_handler_exec;
		sigaction(SIGINT, &act, NULL);
	}
	signal(SIGQUIT, SIG_IGN);
}
