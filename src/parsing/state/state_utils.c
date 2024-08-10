/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:22:40 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/10 21:52:56 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_del_token(t_token **lst, void (*del)(void*))
{
	t_token	*tmp;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		(del)((*lst)->str);
		if (*lst)
			free(*lst);
		*lst = tmp;
	}
}

t_token	*add_to_stack(t_token **buffer, t_token **stack)
{
	t_token	*tmp;
	t_token	*current;

	if (*buffer == NULL)
		return (NULL);
	tmp = *buffer;
	*buffer = (*buffer)->next;
	if (*buffer != NULL)
		(*buffer)->prev = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	if (*stack == NULL)
		*stack = tmp;
	else
	{
		current = *stack;
		while (current->next != NULL)
			current = current->next;
		current->next = tmp;
		tmp->prev = current;
	}
	return (tmp);
}
