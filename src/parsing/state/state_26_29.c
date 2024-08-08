/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_26_29.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:36:59 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/08 17:09:10 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	state_26(t_token	**buffer, t_token *head)
{
	printf("state_26\n");
	ft_del_token(&head, &free);
	insert_token(&head, PIPE_SEQUENCE, NULL);
	state_0(buffer, &head);
}

void	state_27(t_token	**buffer, t_token *head)
{
	printf("state_27\n");
	ft_del_token(&head, &free);
	insert_token(&head, CMD_SUFFIX, NULL);
	state_0(buffer, &head);
}

void	state_28(t_token	**buffer, t_token *head)
{
	printf("state_28\n");
	ft_del_token(&head, &free);
	insert_token(&head, CMD_SUFFIX, NULL);
	state_0(buffer, &head);
}

void	state_29(t_token	**buffer, t_token *head)
{
	printf("state_29\n");
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
