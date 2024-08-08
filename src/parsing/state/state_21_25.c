/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_21_25.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:30:48 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/08 17:08:58 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	state_21(t_token	**buffer, t_token *head)
{
	if (head->type == WORD)
		head->type = CMD_SUFFIX;
	else
	{
		printf("state 21 error\n");
		exit(0);
	}
	state_0(buffer, &head);
}

void	state_22(t_token	**buffer, t_token *head)
{
	const t_assoc	tab[] = {{WORD, state_27}, {OUT, state_2}, {IN, state_3}, \
	{HERE, state_4}, {APPEND, state_5}, {IO_REDIRECT, state_28}, \
	{IO_FILE, state_11}, {IO_HERE, state_12}};
	int				i;

	i = 0;
	while (i < 8)
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
	ft_del_token(&head, &free);
	insert_token(&head, SIMPLE_COMMAND, NULL);
	state_0(buffer, &head);
}

void	state_23(t_token	**buffer, t_token *head)
{
	if (head->type == IO_REDIRECT)
		head->type = CMD_SUFFIX;
	else
	{
		printf("state 23 error\n");
		exit(0);
	}
	state_0(buffer, &head);
}

void	state_24(t_token	**buffer, t_token *head)
{
	const t_assoc	tab[] = {{WORD, state_21}, {OUT, state_2}, {IN, state_3}, \
	{HERE, state_4}, {APPEND, state_5}, {CMD_SUFFIX, state_29}, \
	{IO_REDIRECT, state_28}, {IO_FILE, state_11}, {IO_HERE, state_12}};
	int				i;

	i = 0;
	while (i < 9)
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
	ft_del_token(&head, &free);
	insert_token(&head, SIMPLE_COMMAND, NULL);
	state_0(buffer, &head);
}

void	state_25(t_token	**buffer, t_token *head)
{
	if (head->type == CMD_PREFIX && head->next->type == IO_REDIRECT)
	{
		ft_del_token(&head, &free);
		insert_token(&head, CMD_PREFIX, NULL);
	}
	else
	{
		printf("state 25 error\n");
		exit(0);
	}
	state_0(buffer, &head);
}
