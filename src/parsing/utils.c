/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:49:07 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/18 15:43:37 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_word(char c)
{
	printf("%c\n", c);
	if (ft_isalpha(c) || c == '"' || c == '/' \
		|| c == '_' || c == 39 || c == '.' || c == '~' \
		|| ft_isalnum(c))
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
	t_token			*current;
	const char		*str[4] = {"RIEN", "STACK = ", "BUFFER = ", "START = "};
	const char		*tab[] = {"HERE", "APPEND", "IN", "OUT", "PIPE", "S_AND", \
	"DIEZ", "END", "WORD", "CMD_SUFFIX", "CMD", "CMD_NAME", "SIMPLE_COMMAND", \
	"CMD_SUFFIX", "IO_REDIRECT", "IO_FILE", "IO_HERE", "FILENAME", "eof", \
	"PIPE_SEQUENCE", "CMD_PREFIX"};

	current = head;
	if (current)
	{
		while (current->prev)
			current = current->prev;
	}
	printf("%s", str[whois]);
	while (current != NULL)
	{
		if (current->type >= 0 && current->type < NUMBER_OF_TOKENS)
			printf("%s ", tab[current->type]);
		else
			printf("UNKNOWN ");
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
