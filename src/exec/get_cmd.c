/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 11:44:26 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/13 18:49:27 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd(t_info *var, t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (var->cmd.out >= 0 && var->cmd.out != 1 && \
		(token->type == APPEND || token->type == OUT))
			close(var->cmd.out);
		if (token->type == IN)
			var->cmd.in = open(token->next->str, O_RDONLY);
		else if (token->type == OUT)
			var->cmd.out = open(token->next->str, \
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (token->type == APPEND)
			var->cmd.out = open(token->next->str, \
		O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (check_file_perm(var, token))
			return (var->r);
		if (var->cmd.in >= 0)
			close(var->cmd.in);
		token = token->next;
	}
	return (var->r);
}

int	exec_builtin(t_info *var, t_env **env, t_token *token)
{
	int				i;
	const t_builtin	tab[] = {{"cd", ft_cd}, {"echo", ft_echo}, \
	{"env", ft_env}, {"exit", ft_exit}, {"export", ft_export}, \
	{"pwd", ft_pwd}, {"unset", ft_unset}, {"exit", ft_exit0}};

	var->cmd.out = 1;
	if (get_fd(var, token))
		return (var->r);
	i = -1;
	while (++i < 7)
	{
		if (!ft_strncmp(var->cmd.cmd[0], tab[i].fun, \
		bigger(var->cmd.cmd[0], tab[i].fun)))
		{
			if (!var->n_pipe && i == 3)
				var->r = tab[7].fun_ptr(env, var->cmd.cmd, \
				var->cmd_ln, var->cmd.out);
			else
				var->r = tab[i].fun_ptr(env, var->cmd.cmd, \
				var->cmd_ln, var->cmd.out);
			if (var->cmd.out > 2)
				close(var->cmd.out);
		}
	}
	return (1);
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

	if (!cmd || !ft_strlen(cmd))
		return (NULL);
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
