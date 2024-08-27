/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:22:40 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/27 14:57:38 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_two(t_token **head)
{
	t_token	*last_node;
	t_token	*prev_last;

	last_node = (*head);
	prev_last = (*head)->prev;
	if (prev_last->prev)
		prev_last->prev->next = NULL;
	else
		*head = NULL;
	free(last_node->str);
	free(last_node);
	free(prev_last->str);
	free(prev_last);
}

void	ft_del_token(t_token **lst, void (*del)(void*))
{
	t_token	*tmp;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->prev;
		free((*lst)->str);
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
