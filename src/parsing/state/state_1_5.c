/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_1_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:24:26 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/05 12:59:43 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_5(t_token **buffer, t_token **head)
{
	// printf("state 5\n");
	if ((*head)->type == FILENAME)
		state_18(buffer, head);
	else if ((*head)->type == WORD)
		state_13(buffer, &(*head)->next);
	else if (!(*head)->next && (*buffer)->type == WORD)
	{
		*head = add_to_stack(buffer, head);
		state_13(buffer, head);
	}
	else
	{
		printf("Error state_5\n");
		exit(0);
	}
}

void	state_4(t_token **buffer, t_token **head)
{
	// printf("state 4\n");
	if ((*head)->type == END_F)
		state_17(buffer, head);
	else if ((*head)->type == WORD)
		state_16(buffer, head);
	else if (!(*head)->next && (*buffer)->type == WORD)
	{
		add_to_stack(buffer, head);
		*head = (*head)->next;
		state_16(buffer, head);
	}
	else
	{
		printf("Error state_4\n");
		exit(0);
	}
}

void	state_3(t_token **buffer, t_token **head)
{
	// printf("state 3\n");
	if ((*head)->type == FILENAME)
	{
		if ((*head)->prev)
			*head = (*head)->prev;
		state_15(buffer, head);
	}
	else if ((*head)->type == WORD)
	{
		if ((*head)->next)
			*head = (*head)->next;
		state_13(buffer, head);
	}
	else if (!(*head)->next && (*buffer)->type == WORD)
	{
		add_to_stack(buffer, head);
		*head = (*head)->next;
		state_13(buffer, head);
	}
}

void	state_2(t_token **buffer, t_token **head)
{
	// printf("state 2\n");
	if ((*head)->type == FILENAME)
	{
		*head = (*head)->prev;
		return (state_14(buffer, head));
	}
	else if ((*head)->type == WORD)
		return (state_13(buffer, &((*head)->next)));
	else if (!(*head)->next && (*buffer)->type == WORD)
	{
		add_to_stack(buffer, head);
		*head = (*head)->next;
		return (state_13(buffer, head));
	}
	else
	{
		printf("Error state_2\n");
		exit(0);
	}
}

void	state_1(t_token **buffer, t_token **head)
{
	// printf("state 1\n");
	(void)buffer;
	if (head)
		(*head)->type = CMD_NAME;
	state_0(buffer, head);
}
