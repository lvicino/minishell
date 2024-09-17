/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:50:18 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/17 14:38:13 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_process(t_info	*var)
{
	int	p;

	p = 0;
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

static char	**convert_env(t_env *env)
{
	char	**tab;
	char	*tmp;
	int		ln;

	ln = 1;
	while (env->next)
	{
		ln++;
		env = env->next;
	}
	tab = malloc(sizeof(char *) * (ln + 1));
	if (!tab)
		return (NULL);
	tab[ln] = 0;
	while (--ln >= 0)
	{
		tab[ln] = ft_strjoin(env->var, "=");
		tmp = tab[ln];
		tab[ln] = ft_strjoin(tab[ln], env->value);
		free(tmp);
		env = env->prev;
	}
	return (tab);
}

int	is_builtin(t_info *var, t_token *token)
{
	int				i;
	const char *tab[] = {"cd", "echo", \
	"env", "exit", "export", "pwd", "unset"};

	get_cmd(token, var);
	i = -1;
	while (++i < 7)
	{
		if (var->cmd.cmd && !ft_strncmp(var->cmd.cmd[0], tab[i], \
		bigger(var->cmd.cmd[0], (char *)tab[i])))
			return (1);
	}
	return (0);
}

static int	exec_cmd(t_info *var, t_token **token, t_env **env)
{
	if (is_builtin(var, *token) && exec_builtin(var, env, *token))
		return(free(var->cmd.cmd), freelist(token), free_env(env), var->r);
	var->cmd.path = NULL;
	if (var->cmd.cmd && !ft_strchr(var->cmd.cmd[0], '/'))
		var->cmd.path = get_path(var->cmd.cmd[0], *env);
	else if (var->cmd.cmd && var->cmd.cmd[0])
		var->cmd.path = ft_strdup(var->cmd.cmd[0]);
	if (!var->r && !var->builtin)
	{
		check_cmd_error(var->cmd.cmd, var->cmd.path, &(var->r));
		if (!var->r && var->cmd.path && var->cmd.cmd && var->cmd.cmd[0] &&\
		!access(var->cmd.path, F_OK | X_OK))
			execve(var->cmd.path, var->cmd.cmd, convert_env(*env));
	}
	freelist(token);
	free_env(env);
	if (var->cmd.cmd)
		free(var->cmd.cmd);
	if (var->cmd.path)
		free(var->cmd.path);
	return (var->r);
}

int	exec(t_token **token, t_env **env)
{
	t_info	var; //! set var _= last cmd arg in env when n_pipe = 0


	count_pipe(&var, *token);
	if (!pipeline(&(var.fd), var.n_pipe) || !pipeline(&(var.here), var.n_here))
		return (free_pipeline(&(var.fd), var.n_pipe), \
		free_pipeline(&(var.here), var.n_here), 0);
	make_doc(&var, *token);
	var.builtin = is_builtin(&var, *token) & !var.n_pipe;
	change_var_(var, *env, *token);
	if (!var.r && !var.builtin)
		(free(var.cmd.cmd), get_process(&var));
	if (!var.r && var.pid && !var.builtin)
	{
		free_pipeline(&(var.fd), var.n_pipe);
		free_pipeline(&(var.here), var.n_here);
		return (wait_process(var.pid, var.id, &(var.r)));
	}
	if (!var.r && !var.pid)
	{
		signal_child();
		var.r = choose_pipe(&var, token);
		exit(exec_cmd(&var, token, env));
	}
	exec_builtin(&var, env, *token);
	freelist(token);
	return (free(var.cmd.cmd), var.r);
}
