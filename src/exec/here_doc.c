/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:15:14 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/16 19:09:02 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_sig;

static int	choose_ln(char *eof, char *str)
{
	int	eof_ln;
	int	str_ln;

	eof_ln = ft_strlen(eof);
	str_ln = ft_strlen(str) - 1;
	if (eof_ln > str_ln)
		return (eof_ln);
	else
		return (str_ln);
}

static void	get_eof(t_token **token)
{
	while (*token)
	{
		if ((*token)->next && \
		(*token)->type == HERE && (*token)->next->type == END_F)
		{
			*token = (*token)->next;
			return ;
		}
		*token = (*token)->next;
	}
}

void	make_doc(t_info	*var, t_token *token)
{
	char	*s;
	int		i;
	int		fd;

	i = -1;
	fd = dup(0);
	signal_hd();
	while (++i < var->n_here && !g_sig)
	{
		get_eof(&token);
		s = readline("> ");
		while (s && ft_strncmp(token->str, s, choose_ln(token->str, s)))
		{
			(write(var->here[i][1], s, ft_strlen(s)), free(s));
			s = readline("> ");
		}
		if (s)
			free(s);
		else if (!g_sig)
		{
			ft_putstr_fd("warning: here-document delimited ", 2);
			ft_putstr_fd("by end-of-file (wanted `", 2);
			(ft_putstr_fd(token->str, 2), ft_putstr_fd("')\n", 2));
		}
		else
			free_pipeline(&(var->here), var->n_here);
		var->r = g_sig;
	}
	signal_parent();
	(dup2(fd, 0), close(fd));
}
