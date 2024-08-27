/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:10:24 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/27 15:10:23 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	free_env(t_env **head)
{
	t_env	*tmp;

	if (head == NULL || *head == NULL)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
	}
}

void	set_signal_action(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
}

void	add_node(char *str, t_env **env, char *envp)
{
	t_env	*node;
	t_env	*current;
	int		len;

	len = 0;
	node = malloc(sizeof(t_env));
	node->var = str;
	node->next = NULL;
	while (envp[len] != '=')
		len++;
	node->value = ft_substr(envp, len + 1, ft_strlen(envp));
	if (*env == NULL)
		*env = node;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = node;
		node->prev = current;
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
		while (envp[i][j] != '=')
			j++;
		add_node(ft_substr(envp[i], 0, j), env, envp[i]);
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
	prompt(&env);
	// check expand
	return (0);
}
