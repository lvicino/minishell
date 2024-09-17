/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_11_15.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:54:24 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/17 16:10:08 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_11(t_token	**buffer, t_token **head)
{
	// printf("state 11\n");
	if ((*head)->type == IO_FILE)
		(*head)->type = IO_REDIRECT;
	else
		exit(0);
	state_0(buffer, head);
}

void	state_12(t_token	**buffer, t_token **head)
{
	// printf("state 12\n");
	if ((*head)->type == IO_HERE)
		(*head)->type = IO_REDIRECT;
	else
		exit(0);
	state_0(buffer, head);
}

void	state_13(t_token	**buffer, t_token **head)
{
	// printf("state 13\n");
	if ((*head)->type == WORD)
		(*head)->type = FILENAME;
	else
		exit(0);
	state_0(buffer, head);
}

void	state_14(t_token	**buffer, t_token **head)
{
	// printf("state 14\n");
	if ((*head)->type == FILENAME)
	{
		ft_free_two(head);
		insert_token(head, IO_FILE, NULL);
	}
	else
		exit(0);
	state_0(buffer, head);
}

void	state_15(t_token	**buffer, t_token **head)
{
	// printf("state 15\n");
	if ((*head)->type == FILENAME && (*head)->prev && \
	(*head)->prev->type == IN)
	{
		ft_del_token(head, &free);
		insert_token(head, IO_FILE, NULL);
	}
	else
		exit(0);
	state_0(buffer, head);
}
