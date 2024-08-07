/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:49:07 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/07 14:26:36 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(char c)
{
	if (ft_isalpha(c) || c == '"' || c == '/' \
		|| c == '_' || c == 39 || c == '.' || c == '~')
		return (1);
	return (0);
}

int	bigger(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 > len_s2)
		return (len_s1);
	return (len_s2);
}

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

void	print_tokens(t_token *head, int whois)
{
	t_token	*current;

	current = head;
	if (whois == 1)
		printf("STACK = ");
	else if (whois == 2)
		printf("BUFFER = ");
	else
		printf("START = ");
	while (current != NULL)
	{
		if (current->type == PIPE)
			printf("PIPE");
		if (current->type == END)
			printf("END");
		else if (current->type == OUT)
			printf("OUT");
		else if (current->type == IN)
			printf("IN");
		else if (current->type == HERE)
			printf("H_D");
		else if (current->type == APPEND)
			printf("APPEND");
		else if (current->type == WORD)
			printf("WORD");
		else if (current->type == CMD)
			printf("CMD");
		else if (current->type == S_AND)
			printf("S_AND");
		else if (current->type == DIEZ)
			printf("DIEZcl");
		printf(" ");
		current = current->next;
	}
	printf("\n");
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
