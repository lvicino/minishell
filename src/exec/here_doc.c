/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:15:14 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/09 13:21:43 by lvicino          ###   ########.fr       */
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

	i = -1;
	while (++i < var->n_here)
	{
		(get_eof(&token), write(1, "> ", 2));
		s = get_next_line(0);
		while (s && ft_strncmp(token->str, s, choose_ln(token->str, s)))
		{
			write(var->here[i][1], s, ft_strlen(s));
			(free(s), write(1, "> ", 2));
			s = get_next_line(0);
		}
		if (s)
			free(s);
		else if (!g_sig)
		{
			write(2, "warning: here-document delimited", 32);
			write(2, "by end-of-file (wanted `", 24);
			write(2, token->str, ft_strlen(token->str));
			write(2, "')\n", 3);
		}
		var->r = g_sig;
	}
}
