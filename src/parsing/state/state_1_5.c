/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_1_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubengallien <rubengallien@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:24:26 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/09 16:32:56 by rubengallie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	state_5(t_token **buffer, t_token *head)
{
	printf("5\n");
	if (head->type == FILENAME)
		state_18(buffer, head->next);
	else if (head->type == WORD)
		state_13(buffer, head->next);
	else if (!head->next && (*buffer)->type == WORD)
	{
		add_to_stack(buffer, &head);
		state_13(buffer, head->next);
	}
	else
	{
		printf("Error state_5\n");
		exit(0);
	}
}

void	state_4(t_token **buffer, t_token *head)
{
	printf("4\n");
	if (head->type == eof)
		state_17(buffer, head->next);
	else if (head->type == WORD)
		state_16(buffer, head->next);
	else if (!head->next && (*buffer)->type == WORD)
	{
		add_to_stack(buffer, &head);
		state_16(buffer, head->next);
	}
	else
	{
		printf("Error state_4\n");
		exit(0);
	}
}

void	state_3(t_token **buffer, t_token *head)
{
	printf("3\n");
	if (head->type == FILENAME)
		state_15(buffer, head->next);
	else if (head->type == WORD)
		state_13(buffer, head->next);
	else if (!head->next && (*buffer)->type == WORD)
	{
		add_to_stack(buffer, &head);
		state_13(buffer, head->next);
	}
	else
	{
		printf("Error state_3\n");
		exit(0);
	}
}

void	state_2(t_token **buffer, t_token *head)
{
	printf("2\n");
	if (head->type == FILENAME)
		return (state_14(buffer, head->next));
	else if (head->type == WORD)
		return (state_13(buffer, head->next));
	else if (!head->next && (*buffer)->type == WORD)
	{
		add_to_stack(buffer, &head);
		return (state_13(buffer, head->next));
	}
	else
	{
		printf("Error state_2\n");
		exit(0);
	}
}

void	state_1(t_token **buffer, t_token *head)
{
	printf("1\n");
	(void)buffer;
	if (head)
		head->type = CMD_NAME;
	state_0(buffer, &head);
}
