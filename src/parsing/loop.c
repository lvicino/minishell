/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:33:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/02 13:24:52 by lvicino          ###   ########.fr       */
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
		if (!str)
			return (free_env(env), free(str), clear_history(), \
			ft_printf("exit\n"), 0);
		if (make_tokenize(&token, &stack, &cpy, str))
		{
			add_history(str);
			state_0(&token, &stack);
			if (stack && stack->type == OK)
			{
				printf("OK\n");
				freelist(&stack);
				//ft_expand(&cpy, env);
				print_tokens(cpy, 4);
				exec(cpy, env);
				//exec(ft_expand(&cpy, env), env);
			}
		}
		freelist(&cpy);
		free(str);
	}
}
