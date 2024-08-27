/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_11_15.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:54:24 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/27 12:29:52 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	state_11(t_token	**buffer, t_token **head)
{
	printf("state 11\n");
	if ((*head)->type == IO_FILE)
		(*head)->type = IO_REDIRECT;
	else
	{
		printf("state 11 error\n");
		exit(0);
	}
	state_0(buffer, head);
}

void	state_12(t_token	**buffer, t_token **head)
{
	printf("state 12\n");
	if ((*head)->type == IO_HERE)
		(*head)->type = IO_REDIRECT;
	else
	{
		printf("state 12 error\n");
		exit(0);
	}
	state_0(buffer, head);
}

void	state_13(t_token	**buffer, t_token **head)
{
	printf("state 13\n");
	if ((*head)->type == WORD)
		(*head)->type = FILENAME;
	else
	{
		printf("state 13 error\n");
		exit(0);
	}
	state_0(buffer, head);
}

void	state_14(t_token	**buffer, t_token **head)
{
	int		i;

	i = 0;
	printf("state 14\n");
	if ((*head)->type == OUT && (*head)->next->type == FILENAME)
	{
		*head = (*head)->next;
		ft_free_two(head);
		insert_token(head, IO_FILE, NULL);
	}
	else
	{
		printf("state 14 error\n");
		exit(0);
	}
	state_0(buffer, head);
}

void	state_15(t_token	**buffer, t_token **head)
{
	printf("state 15\n");
	if ((*head)->type == IN && (*head)->next->type == FILENAME)
	{
		ft_del_token(head, &free);
		insert_token(head, IO_FILE, NULL);
	}
	else
	{
		printf("state 15 error\n");
		exit(0);
	}
	state_0(buffer, head);
}
