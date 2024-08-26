/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:54:48 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/26 15:35:51 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file_perm(t_info *var, t_token *token)
{
	if (token->type == END_F)
		return (0);
	if (token->type == IN && access(token->next->str, F_OK))
	{
		var->r = 1;
		if (token->next->str)
			write(2, token->next->str, ft_strlen(token->next->str));
		write(2, ": No such file or directory\n", 28);
	}
	else if (token->type == IN && access(token->next->str, R_OK))
	{
		var->r = 1;
		w_error(token->next->str, 1);
	}
	else if (token->type == OUT && access(token->next->str, W_OK))
	{
		var->r = 1;
		w_error(token->next->str, 1);
	}
	return (var->r);
}

static int	choose_infile(t_info *var, t_token *token, int *i)
{
	if (check_file_perm(var, token))
		return (var->r);
	if (token->type == HERE)
	{
		var->cmd.in = var->here[var->skip_hd + *i][0];
		(*i)++;
	}
	else if (token->type == IN)
		var->cmd.in = open(token->next->str, O_RDONLY);
	if (var->cmd.in < 0 || dup2(var->fd[var->id - 1][0], 0))
		return (1);
}

static int	choose_outfile(t_info *var, t_token *token)
{
	if (check_file_perm(var, token))
		return (var->r);
	if (token->type == APPEND)
		var->cmd.out = open(token->next->str, \
		O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (token->type == OUT)
		var->cmd.out = open(token->next->str, \
		O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (var->cmd.out < 0 || dup2(var->fd[var->id][1], 1))
		return (1);
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
	int	i;

	i = 0;
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
		choose_infile(var, *token, &i)) || \
		(((*token)->type == OUT || (*token)->type == APPEND) && \
		choose_outfile(var, *token)))
			return (free_pipeline(&(var->fd), var->n_pipe), \
			free_pipeline(&(var->here), var->n_here), var->r);
		token = (*token)->next;
	}
	return (free_pipeline(&(var->fd), var->n_pipe), \
	free_pipeline(&(var->here), var->n_here), var->r);
}
