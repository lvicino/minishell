/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:49:07 by rgallien          #+#    #+#             */
/*   Updated: 2024/07/22 16:13:23 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freelist(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->str);
		free(tmp);
	}
}

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		printf("type = %d\n", current->type);
		printf("char *  = %s\n", current->str);
		current = current->next;
	}
}

void	insert_token(t_token **head, t_token_type type, char *str)
{
	t_token	*token;
	t_token	*current ;

	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	token->str = ft_strdup(str);
	token->type = type;
	token->next = NULL;
	if (*head == NULL)
	{
		*head = token;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = token;
}
