/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:22:40 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/08 15:32:10 by rgallien         ###   ########.fr       */
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
		free(*lst);
		*lst = tmp;
	}
}

t_token	*add_to_stack(t_token **buffer, t_token **stack)
{
	t_token	*tmp;
	t_token	*current;

	tmp = *buffer;
	*buffer = (*buffer)->next;
	if (stack && *stack == NULL)
		*stack = tmp;
	else
	{
		current = *stack;
		while (current->next)
			current = current->next;
		current->next = tmp;
	}
	tmp->next = NULL;
	return (tmp);
}
