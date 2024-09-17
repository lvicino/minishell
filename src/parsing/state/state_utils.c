/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:22:40 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/17 12:51:32 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_token(t_token **head, t_token_type type, char *str)
{
	t_token	*token;
	t_token	*current;

	ret_to_start(head);
	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	token->str = ft_strdup(str);
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	if (*head == NULL)
	{
		*head = token;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = token;
	token->prev = current;
}

void	ft_free_two(t_token **head)
{
	t_token	*last_node;
	t_token	*prev_last;
	t_token	*second_node;

	if (!head || !(*head) || !(*head)->prev)
		return;
	last_node = (*head);
	prev_last = last_node->prev;
	if (prev_last->prev)
		second_node = prev_last->prev;
	else
		second_node = NULL;
	if (second_node)
		second_node->next = NULL;
	*head = second_node;
	if (last_node->str)
		free(last_node->str);
	free(last_node);
	if (prev_last->str)
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
