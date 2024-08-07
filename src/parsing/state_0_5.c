/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_0_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:54:04 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/07 17:38:42 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
void prout(int	i)
{
	printf("prout %d\n", i);
}


void	state_0(t_token **buffer, t_token **stack)
{
	t_token		*tmp;
	t_assoc		tab[] = {{WORD, prout}};
	int			i;

	tmp = *stack;
	while (tmp)
	{
		i = 0;
		while (i < 12)
		{
			if (tmp->type == tab[i].type)
				return (tab[i].func(i));
			i++;
		}
		tmp = tmp->next;
	}
	tmp = add_to_stack(buffer, stack);
	i = 0;
	while (i < 12)
	{
		if (tmp->type == tab[i].type)
			return (tab[i].func(i));
		i++;
	}
	// error tokens
}
