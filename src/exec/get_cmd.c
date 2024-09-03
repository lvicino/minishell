/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:44:26 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/03 21:10:22 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_info *var, t_env **env)
{
	int				i;
	const t_builtin tab[] = {{"cd", ft_cd}, {"echo", ft_echo}, \
	{"env", ft_env}, {"exit", ft_exit}, {"export", ft_export}, \
	{"pwd", ft_pwd}, {"unset", ft_unset}};

	i = -1;
	while (++i < 7)
	{
		if (!ft_strncmp(var->cmd.cmd[0], tab[i].fun, \
		bigger(var->cmd.cmd[0], tab[i].fun)))
			return (tab[i].fun_ptr(env, var->cmd.cmd, var->cmd_ln), 1);
	}
	return (0);
}

static char	*find_path(char ***str, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	path = NULL;
	i = 0;
	while (*str && (*str)[i])
	{
		tmp = (*str)[i];
		(*str)[i] = ft_strjoin((*str)[i], "/");
		free(tmp);
		tmp = (*str)[i];
		(*str)[i] = ft_strjoin((*str)[i], cmd);
		free(tmp);
		if (!access((*str)[i], F_OK))
		{
			path = ft_strdup((*str)[i]);
			break ;
		}
		i++;
	}
	ft_free(str);
	return (path);
}

char	*get_path(char *cmd, t_env *env)
{
	char	**str;
	char	*path;

	path = NULL;
	while (env && ft_strncmp(env->var, "PATH", 5))
		env = env->next;
	if (env)
		path = env->value;
	if (!path)
		return (NULL);
	str = ft_split(path, ':');
	path = find_path(&str, cmd);
	return (path);
}

void	get_cmd(t_token *token, t_info *var)
{
	t_token	*tmp;
	int		i;

	i = -1;
	var->cmd_ln = 0;
	tmp = token;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD || tmp->type == CMD_SUFFIX)
			var->cmd_ln++;
		tmp = tmp->next;
	}
	if (!var->cmd_ln)
		var->cmd.cmd = NULL;
	else
		var->cmd.cmd = malloc(sizeof(char *) * (var->cmd_ln + 1));
	if (!var->cmd.cmd)
		return ;
	var->cmd.cmd[var->cmd_ln] = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == CMD || token->type == CMD_SUFFIX)
			var->cmd.cmd[++i] = token->str;
		token = token->next;
	}
}
