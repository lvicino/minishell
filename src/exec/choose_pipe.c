/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:54:48 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/22 14:29:00 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	choose_infile(t_info *var, t_token **token)
{
	*token = (*token)->next;
	if ((*token)->prev->type == HERE)
		var->cmd.in = fd[m_id][0];
	else if ((*token)->prev->type == IN)
		var->cmd.in = open((*token)->next->str, O_RDONLY);
}

static int	choose_outfile(t_info *var, t_token **token)
{
	*token = (*token)->next;
	if ((*token)->prev->type == APPEND)
		var->cmd.out = open((*token)->next->str, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if ((*token)->prev->type == OUT)
		var->cmd.out = open((*token)->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
}

void	set_token(t_info *var, t_token **token)
{
	int	i;

	i = 0;
	while (i != var->id)
	{
		*token = (*token)->next;
		if ((*token)->type == PIPE)
			i++;
		else if ((*token)->type == HERE)
			var->skip_hd++;
	}
	if (i)
		*token = (*token)->next;
}

int	choose_pipe(t_info	*var, t_token **token)
{
	if ((!var->id && dup2(var->fd[var->id][1], 1) < 0) || \
	(var->id == var->n_pipe && dup2(var->fd[var->id - 1][0], 0) < 0) || \
	(var->id && var->id != var->n_pipe && \
	(dup2(var->fd[var->id - 1][0], 0) < 0 || dup2(var->fd[var->id][1], 1) < 0)))
		return (free_pipeline(&(var->fd), var->n_pipe), \
		free_pipeline(&(var->here), var->n_here), 1);
	set_token(var, token);
	while (*token && (*token)->type != PIPE)
	{
		if ((((*token)->type == IN || (*token)->type == HERE) && \
		choose_infile(var, token)) || \
		(((*token)->type == OUT || (*token)->type == APPEND) && \
		choose_outfile(var, token)))
			return (var->r);
		token = (*token)->next;
	}
}
