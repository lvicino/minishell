/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_16_20.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:15:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/08 17:08:22 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	state_16(t_token	**buffer, t_token *head)
{
	if (head->type == WORD)
		head->type = eof;
	else
	{
		printf("state 16 error\n");
		exit(0);
	}
	state_0(buffer, &head);
}

void	state_17(t_token	**buffer, t_token *head)
{
	if (head->type == HERE && head->next->type == eof)
	{
		ft_del_token(&head, &free);
		insert_token(&head, IO_HERE, NULL);
	}
	else
	{
		printf("state 17 error\n");
		exit(0);
	}
	state_0(buffer, &head);
}

void	state_18(t_token	**buffer, t_token *head)
{
	if (head->type == APPEND && head->next->type == FILENAME)
	{
		ft_del_token(&head, &free);
		insert_token(&head, IO_FILE, NULL);
	}
	else
	{
		printf("state 18 error\n");
		exit(0);
	}
	state_0(buffer, &head);
}

void	state_19(t_token	**buffer, t_token *head)
{
	if (head->type == PIPE_SEQUENCE && (*buffer)->type == END)
		printf("GOOD !!\n");
	else
		printf("state 20 error\n");
	exit(0);
}

void	state_20(t_token	**buffer, t_token *head)
{
	const t_assoc	tab[] = {{WORD, state_1}, {OUT, state_2}, {IN, state_3}, \
	{HERE, state_4}, {APPEND, state_5}, {SIMPLE_COMMAND, state_26}, \
	{CMD_NAME, state_8}, {CMD_PREFIX, state_9}, {IO_REDIRECT, state_10},\
	{IO_FILE, state_11}, {IO_HERE, state_12}};
	int				i;

	i = 0;
	while (i < 11)
	{
		if (head->type == tab[i].type)
			return (tab[i].func(buffer, head));
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if (*buffer && (*buffer)->type == tab[i].type)
		{
			head = add_to_stack(buffer, &head);
				return (tab[i].func(buffer, head));
		}
		i++;
	}
	printf("big erreur state 20");
	exit(0);
}

