/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:52:13 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/16 17:28:25 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	sigint_handler_wait(int signal)
{
	if (signal == SIGINT)
	{
		write(0, "\n", 1);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
	}
}

void	sigint_handler_hd(int signal)
{
	if (signal == SIGINT)
	{
		write(0, "\n", 1);
		close(0);
		g_sig = 130;
	}
}

void	sigint_handler_prompt(int signal)
{
	if (signal == SIGINT)
	{
		write(0, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig = 130;
	}
}

void	signal_hd()
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;


	sa_int.sa_handler = sigint_handler_hd;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);  // Appliquer le gestionnaire à SIGINT

	sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);  // Appliquer l'ignorance de SIGQUIT
}

void	signal_wait()
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;


	sa_int.sa_handler = sigint_handler_wait;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);  // Appliquer le gestionnaire à SIGINT

	sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);  // Appliquer l'ignorance de SIGQUIT
}

void	signal_prog()
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;


	sa_int.sa_handler = SIG_DFL;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);  // Appliquer le gestionnaire à SIGINT

	sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);  // Appliquer l'ignorance de SIGQUIT
}

void	initial_signal()
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler_prompt;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);  // Appliquer le gestionnaire à SIGINT

    // Ignorer SIGQUIT
    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);  // Appliquer l'ignorance de SIGQUIT
}