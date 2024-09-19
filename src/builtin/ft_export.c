/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:03 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/19 11:11:47 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_erro_id(char *cmd, int *r)
{
	*r = 1;
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

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

int	print_env_export(t_env **env, int fd)
{
	t_env	*current;

	current = *env;
	while (current && current->var)
	{
		if (ft_strncmp(current->var, "S_PWD", bigger(current->var, "S_PWD")) \
		&& ft_strncmp(current->var, "?", bigger(current->var, "?")))
		{
			ft_putstr_fd("declare -x ", fd);
			ft_putstr_fd(current->var, fd);
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(current->value, fd);
			ft_putstr_fd("\"\n", fd);
		}
		current = current->next;
	}
	return (0);
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

int	ft_export(t_env **env, char **cmd, int cmd_ln, int fd)
{
	int	i;
	int	j;

	i = 0;
	if (cmd_ln == 1)
		fd = print_env_export(env, fd);
	while (cmd[++i] && cmd_ln)
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (cmd[i][j] == '"' || cmd[i][j] == 39 || !ft_isalpha(cmd[i][0]) \
			|| cmd[i][j] == '-')
			{
				write_erro_id(cmd[i], &fd);
				break ;
			}
			if (cmd[i][j] == '=')
			{
				fd = export_env(ft_substr(cmd[i], 0, j), \
				ft_substr(cmd[i], j + 1, ft_strlen(cmd[i]) - (j + 1)), env);
				break ;
			}
		}
	}
	return (fd);
}
