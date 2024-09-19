/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 10:43:40 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/19 12:00:58 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_node(t_token **current, char *str)
{
	t_token	*tmp;

	free((*current)->str);
	if (str)
		free(str);
	if ((*current)->next && (*current)->prev)
	{
		(*current)->prev->next = (*current)->next;
		(*current)->next->prev = (*current)->prev;
	}
	else if (!(*current)->next && (*current)->prev)
		(*current)->prev->next = (*current)->next;
	else if ((*current)->next && !(*current)->prev)
		(*current)->next->prev = (*current)->prev;
	tmp = (*current)->next;
	free(*current);
	*current = tmp;
	ret_to_start(current);
}

int	is_token_two(char *str, int *c, int *i)
{
	const char	*list[] = {"<<", ">>", "<", ">", "|", "&", "#"};

	*i = 0;
	while (*i < END)
	{
		if (!ft_strncmp(str + *c, list[*i], ft_strlen(list[*i])))
			return (1);
		(*i)++;
	}
	return (0);
}

int	bigger(char *s1, char *s2)
{
	int	a;
	int	b;

	a = ft_strlen(s1);
	b = ft_strlen(s2);
	if (a > b)
		return (a);
	return (b);
}
