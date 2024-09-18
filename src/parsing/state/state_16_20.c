/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_16_20.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:15:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/18 16:35:27 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_16(t_token	**buffer, t_token **head)
{
	if ((*head)->type == WORD)
		(*head)->type = END_F;
	else
		state_error(head, buffer);
	state_0(buffer, head);
}

void	state_17(t_token	**buffer, t_token **head)
{
	if ((*head)->type == END_F)
	{
		ft_del_token(head, &free);
		insert_token(head, IO_HERE, NULL);
	}
	else
		state_error(head, buffer);
	state_0(buffer, head);
}

void	state_18(t_token	**buffer, t_token **head)
{
	if ((*head)->type == FILENAME)
	{
		ft_free_two(head);
		insert_token(head, IO_FILE, NULL);
	}
	else
		state_error(head, buffer);
	state_0(buffer, head);
}

void	state_19(t_token	**buffer, t_token **head)
{
	t_token	*tmp;

	*buffer = NULL;
	if ((*head)->type == END)
	{
		while (*head)
		{
			tmp = (*head)->prev;
			free((*head)->str);
			free(*head);
			*head = tmp;
		}
		insert_token(head, OK, NULL);
		return ;
	}
	else
		state_error(head, buffer);
}

void	state_20(t_token	**buffer, t_token **head)
{
	t_assoc			*tab;
	int				i;

	i = -1;
	tab = get_tab(20);
	while (++i < 11)
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
	state_error(head, buffer);
}
