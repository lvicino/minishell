/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:22:32 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/19 10:44:16 by lvicino          ###   ########.fr       */
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
		if (token->type == IN && \
		token->next && token->next->type == FILENAME)
			var->cmd.in = open(token->next->str, O_RDONLY);
		else if (token->type == OUT && \
		token->next && token->next->type == FILENAME)
			var->cmd.out = open(token->next->str, \
			O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (token->type == APPEND && \
		token->next && token->next->type == FILENAME)
			var->cmd.out = open(token->next->str, \
			O_WRONLY | O_CREAT | O_APPEND, 0666);
		if ((token->type == IN || token->type == OUT || token->type == APPEND) \
		&& check_file_perm(var, token))
			return (var->r);
		if (var->cmd.in >= 0)
			close(var->cmd.in);
		token = token->next;
	}
	return (var->r);
}

int	exec_builtin(t_info *var, t_env **env, t_token **token)
{
	int				i;
	const t_builtin	tab[] = {{"cd", ft_cd}, {"echo", ft_echo}, \
	{"env", ft_env}, {"exit", ft_exit}, {"export", ft_export}, \
	{"pwd", ft_pwd}, {"unset", ft_unset}, {"exit", ft_exit0}};

	var->cmd.out = 1;
	if (var->r || get_fd(var, *token))
		return (var->r);
	i = -1;
	while (++i < 7)
	{
		if (!ft_strncmp(var->cmd.cmd[0], tab[i].fun, \
		bigger(var->cmd.cmd[0], tab[i].fun)))
		{
			if (!var->n_pipe && i == 3)
			{
				var->r = tab[7].fun_ptr(env, var->cmd.cmd, \
				var->cmd_ln, var->cmd.out);
				(freelist(token), free(var->cmd.cmd), exit(var->r));
			}
			else
				var->r = tab[i].fun_ptr(env, var->cmd.cmd, \
				var->cmd_ln, var->cmd.out);
			if (var->cmd.out > 2)
				close(var->cmd.out);
		}
	}
	return (1);
}
