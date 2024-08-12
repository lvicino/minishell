/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_26_29.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:36:59 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/12 14:59:31 by rgallien         ###   ########.fr       */
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
	int		i;
	t_token	*tmp;

	tmp = head;
	i = 0;
	printf("state_27\n");
	while (i < 2 && head)
	{
		tmp = head->prev;
		if (tmp)
			tmp->next = NULL;
		head->prev->next = NULL;
		free(head->str);
		free(head);
		head = tmp;
		i++;
	}
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
