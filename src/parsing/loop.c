/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:33:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/28 15:52:09 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt(t_env	**env)
{
	char	*str;
	t_token	*token;
	t_token	*stack;
	t_token	*cpy;

	while (1)
	{
		str = readline("Minishell: ");
		if (!str || !ft_strncmp(str, "exit", bigger(str, "exit")))
			return (free_env(env), free(str), clear_history(), \
			ft_printf("exit\n"), 0);
		add_history(str);
		if (make_tokenize(&token, &stack, &cpy, str))
			state_0(&token, &stack);
		if (stack && stack->type == OK)
			exec(cpy, env);
		freelist(&cpy);
		freelist(&stack);
		free(str);
	}
}
