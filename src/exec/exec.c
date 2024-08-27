/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:50:18 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/27 14:17:09 by lvicino          ###   ########.fr       */
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

static int	exec_cmd(t_info *var, t_token *token, t_env **env)
{
	get_cmd(token, var);
	// if (is_builtin(var->cmd.cmd, env, &(var->r)));
	// 	return(free(var->cmd.cmd), var->r);
	var->cmd.path = NULL;
	if (var->cmd.cmd && !ft_strchr(var->cmd.cmd[0], '/'))
		var->cmd.path = get_path(var->cmd.cmd[0], *env);
	else if (var->cmd.cmd && var->cmd.cmd[0])
		var->cmd.path = ft_strdup(var->cmd.cmd[0]);
	check_cmd_error(var->cmd.cmd, var->cmd.path, &(var->r));
	if (var->cmd.path && var->cmd.cmd && !access(var->cmd.path, F_OK | X_OK))
		execve(var->cmd.path, var->cmd.cmd, NULL); //! env?
	if (var->cmd.cmd)
		free(var->cmd.cmd);
	if (var->cmd.path)
		free(var->cmd.path);
	return (var->r);
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
		var.r = choose_pipe(&var, &token);
	if (!var.pid && !var.r)
		exit(exec_cmd(&var, token, env));
	return (var.r);
}
