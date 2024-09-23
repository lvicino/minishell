/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:33:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/20 17:46:52 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*prompt_pwd(t_env	**env)
{
	char	*str;
	char	*tmp;
	t_env	*node;

	str = NULL;
	node = *env;
	while (node && ft_strncmp(node->var, "PWD", bigger(node->var, "PWD")))
		node = node->next;
	if (node)
		str = node->value;
	else
	{
		node = *env;
		while (node && ft_strncmp(node->var, \
		"S_PWD", bigger(node->var, "S_PWD")))
			node = node->next;
		if (node)
			str = node->value;
	}
	if (str)
	{
		tmp = ft_strjoin("minishell:", str);
		free(str);
		if (tmp)
		{
			str = ft_strjoin(tmp, "$ ");
			free(tmp);
		}
	}
	printf("str = %s%%\n", str);
	return (readline(str));
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
		// str = prompt_pwd(env);
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
