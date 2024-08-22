/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:10:24 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/22 13:45:16 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "termios.h"

void	set_signal_action(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));

}

void	print_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}

void	add_node(char *str, t_env **env)
{
	t_env	*node;
	t_env	*current;
	int		len;

	len = 0;
	node = malloc(sizeof(t_env));
	node->value = str;
	node->next = NULL;
	while (str[len] != '=')
		len++;
	node->var = ft_substr(str, 0, len);
	if (*env == NULL)
		*env = node;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = node;
	}
}

void	make_env(t_env **env, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
			j++;
		add_node(ft_substr(envp[i], 0, j), env);
		i++;
	}
}

int	main(int ac, char **ar, char **envp)
{
	t_env	*env;

	env = NULL;
	(void)ar;
	if (ac != 1)
		return (-1);
	make_env(&env, envp);
	print_env(env);
	prompt(&env);
	return (0);
}
