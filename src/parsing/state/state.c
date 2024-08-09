/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubengallien <rubengallien@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:54:04 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/09 16:13:10 by rubengallie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_assoc	*get_tab_2(int state)
{
	static t_assoc	tab_22[] = {{WORD, state_27}, {OUT, state_2}, {IN, \
	state_3}, {HERE, state_4}, {APPEND, state_5}, {IO_REDIRECT, state_27}, \
	{IO_FILE, state_11}, {IO_HERE, state_12}};
	static t_assoc	tab_24[] = {{WORD, state_21}, {OUT, state_2}, {IN, \
	state_3}, {HERE, state_4}, {APPEND, state_5}, {CMD_SUFFIX, state_29}, \
	{IO_REDIRECT, state_23}, {IO_FILE, state_11}, {IO_HERE, state_12}};
	static t_assoc	tab_29[] = {{WORD, state_27}, {OUT, state_2}, {IN, \
	state_3}, {HERE, state_4}, {APPEND, state_5}, {IO_REDIRECT, state_28}, \
	{IO_FILE, state_11}, {IO_HERE, state_12}};

	if (state == 22)
		return (tab_22);
	else if (state == 24)
		return (tab_24);
	else if (state == 29)
		return (tab_29);
	return (NULL);
}

t_assoc	*get_tab(int state)
{
	static t_assoc	tab_0[] = {{WORD, state_1}, {OUT, state_2}, {IN, \
	state_3}, {HERE, state_4}, {APPEND, state_5}, {PIPE_SEQUENCE, state_6}, \
	{SIMPLE_COMMAND, state_7}, {CMD_NAME, state_8}, {CMD_PREFIX, state_9}, \
	{IO_REDIRECT, state_10}, {IO_FILE, state_11}, {IO_HERE, state_12}};
	static t_assoc	tab_8[] = {{WORD, state_21}, {OUT, state_2}, {IN, \
	state_3}, {HERE, state_4}, {APPEND, state_5}, {CMD_SUFFIX, state_22}, \
	{IO_REDIRECT, state_23}, {IO_FILE, state_11}, {IO_HERE, state_12}};
	static t_assoc	tab_9[] = {{WORD, state_1}, {OUT, state_2}, {IN, \
	state_3}, {HERE, state_4}, {APPEND, state_5}, {CMD_NAME, state_24}, \
	{IO_REDIRECT, state_25}, {IO_FILE, state_11}, {IO_HERE, state_12}};
	static t_assoc	tab_20[] = {{WORD, state_1}, {OUT, state_2}, {IN, \
	state_3}, {HERE, state_4}, {APPEND, state_5}, {SIMPLE_COMMAND, state_26}, \
	{CMD_NAME, state_8}, {CMD_PREFIX, state_9}, {IO_REDIRECT, state_10}, \
	{IO_FILE, state_11}, {IO_HERE, state_12}};

	if (state == 0)
		return (tab_0);
	else if (state == 8)
		return (tab_8);
	else if (state == 9)
		return (tab_9);
	else if (state == 20)
		return (tab_20);
	else
		return (get_tab_2(state));
}

void	state_0(t_token **buffer, t_token **stack)
{
	t_token			*tmp;
	t_assoc			*tab;
	int				i;

	tab = get_tab(0);
	tmp = *stack;
	printf("0\n");
	print_tokens(*stack, 1);
	print_tokens(*buffer, 2);
	while (tmp)
	{
		i = -1;
		while (++i < 12)
		{
			if (tmp->type == tab[i].type)
				return (tab[i].func(buffer, tmp));
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
