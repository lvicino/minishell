/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:06 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/18 17:26:39 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*unset_var(t_env **env)
{
	t_env	*node;
	t_env	*next;
	t_env	*prev;

	node = *env;
	next = node->next;
	prev = node->prev;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (node->var)
		free(node->var);
	if (node->value)
		free(node->value);
	free(node);
	return (next);
}

int	ft_unset(t_env **env, char **cmd, int cmd_ln, int fd)
{
	t_env	*node;
	int		i;

	(void)fd;
	if (cmd_ln == 1)
		return (0);
	node = *env;
	while (node)
	{
		i = 0;
		while (cmd[++i])
		{
			if (!ft_strncmp(node->var, cmd[i], bigger(node->var, cmd[i])) && \
			ft_strncmp(node->var, "?", bigger(node->var, "?")) && \
			ft_strncmp(node->var, "_", bigger(node->var, "_")) && \
			ft_strncmp(node->var, "S_PWD", bigger(node->var, "S_PWD")))
			{
				node = unset_var(&node);
				break ;
			}
		}
		if (!cmd[i])
			node = node->next;
	}
	return (0);
}
