/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_16_20.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubengallien <rubengallien@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:15:05 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/16 15:57:03 by rubengallie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	state_16(t_token	**buffer, t_token *head)
{
	printf("state 16\n");
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
	printf("state 17\n");
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
	printf("state 18\n");
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
	(void)buffer;
	printf("state 19\n");
	if (head->type == END)
		printf("GOOD !!\n");
	else
		printf("state 19 error\n");
}

void	state_20(t_token	**buffer, t_token *head)
{
	t_assoc			*tab;
	int				i;

	i = 0;
	tab = get_tab(20);
	printf("state 20\n");
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
	state_error(head->str);
	exit(0);
}
