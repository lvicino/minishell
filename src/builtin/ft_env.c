/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:01 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/20 11:12:17 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_var_(t_info *var, t_env *env, t_token *token)
{
	int		i;
	char	*path;

	if (var->n_pipe)
		return ;
	i = 0;
	while (var->cmd.cmd && var->cmd.cmd[i + 1])
		i++;
	while (env && ft_strncmp(env->var, "_", bigger(env->var, "_")))
		env = env->next;
	if (env)
	{
		path = NULL;
		if (!i && var->cmd.cmd)
			path = get_path(var->cmd.cmd[0], env);
		free(env->value);
		if (var->cmd.cmd && (is_builtin(*var, token) || !path))
			env->value = ft_strdup(var->cmd.cmd[i]);
		else if (var->cmd.cmd && path)
			env->value = path;
		else
			env->value = ft_strdup("");
		if (path && is_builtin(*var, token))
			free(path);
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
	if (str)
		node->var = str;
	else
		node->var = NULL;
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
	add_node(ft_strdup("S_PWD"), env, "S_PWD=NULL");
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
		if (ft_strncmp(current->var, "?", bigger(current->var, "?")) \
		&& ft_strncmp(current->var, "S_PWD", bigger(current->var, "S_PWD")))
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
