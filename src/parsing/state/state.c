/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:54:04 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/08 17:56:21 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_assoc	*get_tab(int state)
{
	const t_assoc	tab_0[] = {{WORD, state_1}, {OUT, state_2}, {IN, state_3}, \
	{HERE, state_4}, {APPEND, state_5}, {PIPE_SEQUENCE, state_6}, \
	{SIMPLE_COMMAND, state_7}, {CMD_NAME, state_8}, {CMD_PREFIX, state_9}, \
	{IO_REDIRECT, state_10}, {IO_FILE, state_11}, {IO_HERE, state_12}};
	const t_assoc	tab_8[] = {{WORD, state_21}, {OUT, state_2}, {IN, state_3}, \
	{HERE, state_4}, {APPEND, state_5}, {CMD_SUFFIX, state_22}, \
	{IO_REDIRECT, state_23}, {IO_FILE, state_11}, {IO_HERE, state_12}};
	const t_assoc	tab_9[] = {{WORD, state_1}, {OUT, state_2}, {IN, state_3}, \
	{HERE, state_4}, {APPEND, state_5}, {CMD_NAME, state_24}, \
	{IO_REDIRECT, state_25}, {IO_FILE, state_11}, {IO_HERE, state_12}};
	const t_assoc	tab[] =

	if (state == 0)
		return (tab_0);
	if (state == 8)
		return (tab_8);
}

void	state_0(t_token **buffer, t_token **stack)
{
	t_token			*tmp;
	t_assoc	*tab;
	int				i;

	tab = get_tab(0);
	tmp = *stack;
	while (tmp)
	{
		i = -1;
		while (++i < 12)
		{
			if (tmp->type == tab[i].type)
				return (tab[i].func(buffer, &tmp->next));
		}
		tmp = tmp->next;
	}
	tmp = add_to_stack(buffer, stack);
	i = -1;
	while (++i < 12)
	{
		if (tmp->type == tab[i].type)
			return (tab[i].func(buffer, tmp));
	}
}
