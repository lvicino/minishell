/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:01 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/03 11:55:20 by rgallien         ###   ########.fr       */
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

int	ft_env(t_env **env, char **cmd, int cmd_ln)
{
	t_env	*current;

	(void)cmd;
	current = *env;
	if (cmd_ln > 1)
		return (125);
	while (current)
	{
		printf("%s=%s\n", current->var, current->value);
		current = current->next;
	}
	return (0);
}
