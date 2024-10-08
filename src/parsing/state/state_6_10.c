/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_6_10.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:20:32 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/18 16:25:29 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_6(t_token **buffer, t_token **head)
{
	if (!(*head)->next)
		*head = add_to_stack(buffer, head);
	if ((*head)->type == END)
		state_19(buffer, head);
	else if ((*head)->type == PIPE)
	{
		if ((*head)->next)
			*head = (*head)->next;
		state_20(buffer, head);
	}
	else
		state_error(head, buffer);
}

void	state_7(t_token	**buffer, t_token **head)
{
	if ((*head)->type == SIMPLE_COMMAND)
	{
		(*head)->type = PIPE_SEQUENCE;
		state_0(buffer, head);
	}
	else
		state_error(head, buffer);
}

void	state_8(t_token **buffer, t_token **head)
{
	const t_assoc	*tab;
	int				i;

	i = -1;
	tab = get_tab(8);
	while (head && ++i < 9)
	{
		if ((*head)->type == tab[i].type)
		{
			if ((*head)->next)
				*head = (*head)->next;
			return (tab[i].func(buffer, head));
		}
	}
	i = -1;
	while (++i < 5)
	{
		if (*buffer && (*buffer)->type == tab[i].type)
		{
			*head = add_to_stack(buffer, head);
			return (tab[i].func(buffer, head));
		}
	}
	(ft_del_token(head, &free), insert_token(head, SIMPLE_COMMAND, NULL));
	state_0(buffer, head);
}

void	state_9(t_token	**buffer, t_token **head)
{
	const t_assoc	*tab;
	int				i;

	tab = get_tab(9);
	i = -1;
	while (++i < 9)
	{
		if ((*head)->type == tab[i].type)
		{
			if ((*head)->next)
				*head = (*head)->next;
			return (tab[i].func(buffer, head));
		}
	}
	i = -1;
	while (++i < 5)
	{
		if (*buffer && (*buffer)->type == tab[i].type)
		{
			*head = add_to_stack(buffer, head);
			return (tab[i].func(buffer, head));
		}
	}
	ft_del_token(head, &free);
	(insert_token(head, SIMPLE_COMMAND, NULL), state_0(buffer, head));
}

void	state_10(t_token	**buffer, t_token **head)
{
	if ((*head)->type == IO_REDIRECT)
		(*head)->type = CMD_PREFIX;
	else
		state_error(head, buffer);
	state_0(buffer, head);
}
