/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_26_29.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubengallien <rubengallien@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:36:59 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/09 12:32:17 by rubengallie      ###   ########.fr       */
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
	t_assoc			*tab;
	int				i;

	printf("state_29\n");
	i = 0;
	tab = get_tab(29);
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
