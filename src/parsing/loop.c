/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:33:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/07 17:06:27 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_exit_value(int value, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current && ft_strncmp(current->var, "?", bigger(current->var, "?")))
		current = current->next;
	if (current)
	{
		free(current->value);
		current->value = ft_itoa(value);
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
		str = readline("Minishell: ");
		if (!str)
			return (free_env(env), free(str), clear_history(), \
			ft_printf("exit\n"), 0);
		if (make_tokenize(&token, &stack, &cpy, str))
		{
			add_history(str);
			state_0(&token, &stack);
			if (stack && stack->type == OK)
			{
				freelist(&stack);
				ft_expand(&cpy, env);
				get_exit_value(exec(&cpy, env), env);
			}
		}
		freelist(&cpy);
		free(str);
	}
}
