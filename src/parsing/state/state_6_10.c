/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_6_10.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubengallien <rubengallien@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:20:32 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/09 16:50:17 by rubengallie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	state_6(t_token **buffer, t_token *head)
{
	printf("6\n");
	if (!head->next){
		head = add_to_stack(buffer, &head);
	}
	if (head->type == END)
		state_19(buffer, head);
	else if (head->type == PIPE)
		state_20(buffer, head);
	else
	{
		printf("error state_6\n");
		exit(0);
	}
}

void	state_7(t_token	**buffer, t_token *head)
{
	printf("7\n");
	if (head->type == SIMPLE_COMMAND)
	{
		head->type = PIPE_SEQUENCE;
		state_0(buffer, &head);
	}
	else
	{
		printf("error state_7\n");
		exit(0);
	}
}

void	state_8(t_token **buffer, t_token *head)
{
	const t_assoc	*tab;
	int				i;

	i = 0;
	tab = get_tab(8);
	printf("8\n");
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

void	state_9(t_token	**buffer, t_token *head)
{
	const t_assoc	*tab;
	int				i;

	tab = get_tab(9);
	i = 0;
	printf("9\n");
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

void	state_10(t_token	**buffer, t_token *head)
{
	printf("10\n");
	if (head->type == IO_REDIRECT)
		head->type = CMD_PREFIX;
	else
	{
		printf("state 10 error\n");
		exit(0);
	}
	state_0(buffer, &head);
}
