/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:15:14 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/20 14:44:41 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	choose_ln(char *eof, char *str)
{
	int	eof_ln;
	int	str_ln;

	eof_ln = ft_strlen(eof);
	str_ln = ft_strlen(str);
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

static void	w_doc(t_info *var, t_token *token, char *s, int i)
{
	while (++i < var->n_here && !g_sig)
	{
		get_eof(&token);
		s = readline("> ");
		while (s && ft_strncmp(token->str, s, choose_ln(token->str, s)))
		{
			(write(var->here[i][1], s, ft_strlen(s)), free(s));
			(write(var->here[i][1], "\n", 1), s = readline("> "));
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
}

void	make_doc(t_info *var, t_token *token)
{
	char	*s;
	int		i;
	int		fd;

	i = -1;
	s = NULL;
	fd = dup(0);
	signal_hd();
	w_doc(var, token, s, i);
	signal_parent();
	dup2(fd, 0);
	close(fd);
}
