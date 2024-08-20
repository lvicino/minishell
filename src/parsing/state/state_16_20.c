/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_16_20.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:15:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/20 17:39:49 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	state_16(t_token	**buffer, t_token **head)
{
	printf("state 16\n");
	if ((*head)->type == WORD)
		(*head)->type = eof;
	else
	{
		printf("state 16 error\n");
		exit(0);
	}
	state_0(buffer, head);
}

void	state_17(t_token	**buffer, t_token **head)
{
	printf("state 17\n");
	if ((*head)->type == eof)
	{
		ft_del_token(head, &free);
		insert_token(head, IO_HERE, NULL);
	}
	else
	{
		printf("state 17 error\n");
		exit(0);
	}
	state_0(buffer, head);
}

void	state_18(t_token	**buffer, t_token **head)
{
	printf("state 18\n");
	if ((*head)->type == APPEND && (*head)->next->type == FILENAME)
	{
		ft_del_token(head, &free);
		insert_token(head, IO_FILE, NULL);
	}
	else
	{
		printf("state 18 error\n");
		exit(0);
	}
	state_0(buffer, head);
}

void	state_19(t_token	**buffer, t_token **head)
{
	printf("state 19\n");
	(void)buffer;
	if ((*head)->type == END)
	{
		// freelist(head);
		printf("OK\n");
	}
	else
		printf("state 19 error\n");
}

void	state_20(t_token	**buffer, t_token **head)
{
	t_assoc			*tab;
	int				i;

	printf("state 20, type = %d\n", (*head)->type);
	// print_tokens(*head, 1);
	// print_tokens(*buffer, 2);
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
