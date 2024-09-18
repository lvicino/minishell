/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:30:46 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/18 16:39:00 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

void	sigint_handler_hd(int signal)
{
	if (signal == SIGINT)
	{
		write(0, "\n", 1);
		close(0);
		g_sig = 130;
	}
}

void	sigint_handler_parent(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		g_sig = 130;
	}
}

void	sigint_handler_prompt(int signal)
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
