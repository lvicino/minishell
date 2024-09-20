/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:33:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/20 13:15:05 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_sig;

void	get_g_sig(t_env **env)
{
	if (g_sig)
	{
		if ((*env) && (*env)->value)
			free((*env)->value);
		(*env)->value = ft_itoa(g_sig);
	}
	g_sig = 0;
}

void	get_exit_value(int value, t_env **env)
{
	if ((*env))
	{
		free((*env)->value);
		(*env)->value = ft_itoa(value);
	}
}

int	prompt(t_env	**env)
{
	char	*str;
	t_token	*token;
	t_token	*stack;
	t_token	*cpy;

	while (1)
	{
		initial_signal();
		str = readline("Minishell: ");
		if (!str)
			return (free_env(env), free(str), clear_history(), \
			ft_printf("exit\n"), 0);
		if (make_tokenize(&token, &stack, &cpy, str))
		{
			(add_history(str), state_0(&token, &stack));
			if (stack && stack->type == OK)
			{
				get_g_sig(env);
				(freelist(&stack), ft_expand(&cpy, env), tokenize_cpy(cpy, 0));
				get_exit_value(exec(&cpy, env), env);
			}
		}
		freelist(&cpy);
		free(str);
	}
}
