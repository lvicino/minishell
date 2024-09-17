/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 13:37:04 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/16 19:05:13 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_pipe(t_info *var, t_token *token)
{
	var->n_pipe = 0;
	var->n_here = 0;
	var->pid = 1;
	var->id = -1;
	var->r = 0;
	var->cmd.in = -1;
	var->cmd.out = -1;
	while (token)
	{
		if (token->type == PIPE)
			var->n_pipe++;
		else if (token->type == HERE)
			var->n_here++;
		token = token->next;
	}
}

int	wait_process(pid_t pid, int id, int *r)
{
	int	status;
	int	n;

	n = id;
	signal_parent();
	while (id >= 0)
	{
		if (pid == wait(&status))
		{
			*r = WEXITSTATUS(status);
		}
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			if (id == n)
				*r = 130;
		}
		id--;
	}

	initial_signal();
	return (*r);
}

void	ft_free(char ***str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		free((*str)[i]);
		i++;
	}
	free(*str);
	*str = NULL;
}

void	free_pipeline(int ***fd, int i)
{
	while (--i >= 0 && *fd)
	{
		close((*fd)[i][0]);
		close((*fd)[i][1]);
		free((*fd)[i]);
	}
	if (*fd)
		free(*fd);
	*fd = NULL;
}

int	pipeline(int ***tab, int n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		*tab = NULL;
		return (1);
	}
	*tab = (int **)malloc(sizeof(int *) * (n));
	if (!*tab)
		return (0);
	while (i < n)
	{
		(*tab)[i] = (int *)malloc(sizeof(int) * (2));
		if (!(*tab)[i] || pipe((*tab)[i]))
		{
			if ((*tab)[i])
				free((*tab)[i]);
			free_pipeline(tab, i);
			return (0);
		}
		i++;
	}
	return (1);
}
