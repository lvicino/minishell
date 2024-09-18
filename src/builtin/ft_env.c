/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:01 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/18 15:53:48 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_var_(t_info *var, t_env *env)
{
	int	i;
	char *tmp;

	if (var->n_pipe)
		return ;
	i = 0;
	while (var->cmd.cmd && var->cmd.cmd[i + 1])
		i++;
	while (env && ft_strncmp(env->var, "_", bigger(env->var, "_")))
		env = env->next;
	if (env)
	{
		free(env->value);
		if (var->cmd.cmd)
			env->value = ft_strdup(var->cmd.cmd[i]);
		else
			env->value = ft_strdup("");
	}
	tmp = get_path(env->value, env);
	if (tmp)
	{
		free(env->value);
		env->value = tmp;
	}
}

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
	node->value = ft_substr(envp, len + 1, ft_strlen(envp) - (len + 1));
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
	add_node(ft_strdup("?"), env, "?=0");
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		add_node(ft_substr(envp[i], 0, j), env, envp[i]);
		i++;
	}
}

int	ft_env(t_env **env, char **cmd, int cmd_ln, int fd)
{
	t_env	*current;

	(void)cmd;
	current = *env;
	if (cmd_ln > 1)
		return (125);
	while (current)
	{
		if (ft_strncmp(current->var, "?", bigger(current->var, "?")))
		{
			ft_putstr_fd(current->var, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(current->value, fd);
			ft_putstr_fd("\n", fd);
		}
		current = current->next;
	}
	return (0);
}
