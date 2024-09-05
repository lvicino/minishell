/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:03 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/05 19:30:19 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_before_last(char *var, char *value, t_env **env)
{
	t_env	*node;
	t_env	*before_last;

	before_last = *env;
	node = malloc(sizeof(t_env));
	node->var = var;
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	while (before_last->next && \
	ft_strncmp(before_last->next->var, "_", bigger(before_last->var, "_")))
			before_last = before_last->next;
	if (before_last->next)
	{
		node->next = before_last->next;
		before_last->next = node;
		node->prev = before_last;
		node->next->prev = node;
	}
	else
	{
		before_last->next = node;
		node->prev = before_last;
	}

}

int	export_env(char *var, char *value, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current && ft_strncmp(current->var, var, bigger(current->var, var)))
		current = current->next;
	if (current)
	{
		free(current->value);
		free(var);
		current->value = value;
	}
	else
		add_before_last(var, value, env);
	return (0);
}

int	ft_export(t_env **env, char **cmd, int cmd_ln)
{
	int	r;
	int	i;
	int	j;
	int	start;

	(void)cmd_ln;
	r = 0;
	i = 0;
	while (cmd[++i])
	{
		start = 0;
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '"' || cmd[i][j] == 39 || !ft_isalpha(cmd[i][0]))
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(cmd[i],2 );
				ft_putstr_fd("': not a valid identifier\n", 2);
				r = 1;
				break;
			}
			if (cmd[i][j] == '=')
			{
				r = export_env(ft_substr(cmd[i], start, j), \
				ft_substr(cmd[i], j + 1, ft_strlen(cmd[i]) - (j + 1)), env);
				break;
			}
			j++;
		}
	}
	return (r);
}
