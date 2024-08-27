/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:44:26 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/27 14:24:59 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		{
			var->cmd.cmd[++i] = token->str;
		}
	}
}
