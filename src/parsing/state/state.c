/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:54:04 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/10 01:59:05 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ret_to_start(t_token **head)
{
	if (head == NULL || *head == NULL)
		return ;
	while (*head && (*head)->prev)
		*head = (*head)->prev;
}

void	state_error(t_token **head, t_token **buffer)
{
	write(2, "minishell : syntax error near unexpected token ", 48);
	write(2, "` ", 1);
	ft_putstr_fd((*head)->str, 2);
	write(2, "'\n", 2);
	freelist(head);
	freelist(buffer);
	return ;
}

t_assoc	*get_tab_2(int state)
{
	static t_assoc	tab_22[] = {{WORD, state_27}, {OUT, state_2}, {IN, \
	state_3}, {HERE, state_4}, {APPEND, state_5}, {IO_REDIRECT, state_28}, \
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

int	state_0(t_token **buffer, t_token **stack)
{
	t_assoc			*tab;
	int				i;

	tab = get_tab(0);
	ret_to_start(stack);
	i = -1;
	while (++i < 12)
	{
		if (*stack && (*stack)->type == tab[i].type)
		{
			if ((*stack)->next)
				*stack = (*stack)->next;
			return (tab[i].func(buffer, stack), 1);
		}
	}
	*stack = add_to_stack(buffer, stack);
	i = -1;
	while (++i < 12)
	{
		if ((*stack)->type == tab[i].type)
			return (tab[i].func(buffer, stack), 1);
	}
	state_error(stack, buffer);
	return (0);
}
