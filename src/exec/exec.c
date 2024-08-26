/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:50:18 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/23 17:48:47 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_process(t_info	*var)
{
	int	p;

	p = 0;
	var->id = -1;
	var->pid = 1;
	var->r = 0;
	while (var->pid && var->id < var->n_pipe)
	{
		var->pid = fork();
		if (var->pid < 0)
			p++;
		var->id++;
	}
	if (var->pid)
		var->id -= p;
}

static int	exec_cmd(char **argv, char **envp, int id)
{
	char	**cmd;
	char	*path;
	int		r;

	r = 0;
	cmd = get_cmd(argv, id);
	path = NULL;
	if (cmd && !ft_strchr(cmd[0], '/'))
		path = get_path(cmd[0], envp);
	else if (cmd && cmd[0])
		path = ft_strdup(cmd[0]);
	check_cmd_error(cmd, path, &r);
	if (path && cmd && !access(path, F_OK | X_OK))
		execve(path, cmd, envp);
	if (cmd)
		ft_free(&cmd);
	if (path)
		free(path);
	return (r);
}

int	exec(t_token *token, t_env **env)
{
	t_info	var;

	count_pipe(&var, token);
	if (!pipeline(&(var.fd), var.n_pipe))
		return (0);
	if (!pipeline(&(var.here), var.n_here))
		return (free_pipeline(&(var.fd), var.n_pipe), 0);
	make_doc(&var, token);
	get_process(&var);
	if (var.pid)
	{
		free_pipeline(&(var.fd), var.n_pipe);
		free_pipeline(&(var.here), var.n_here);
		wait_process(var.pid, var.id, &(var.r));
	}
	if (!var.pid)
		var.r = choose_pipe(&var, &token); //! in progress
	if (!var.pid && !var.r)
		var.r = exec_cmd(token, env, var);
	return (var.r);
}
