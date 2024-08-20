/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:49:07 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/20 16:44:57 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || \
	c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_word(char c)
{
	if (ft_isalpha(c) || c == '"' || c == '/' \
		|| c == '_' || c == 39 || c == '.' || c == '~' \
		|| ft_isalnum(c) || c == '=')
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

void	freelist(t_token **head)
{
	t_token	*tmp;

	ret_to_start(head);
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->str);
		free(tmp);
		tmp = NULL;
	}
}

void	print_tokens(t_token *head, int whois)
{
	const char		*str[5] = {"RIEN", "STACK = ", "BUFFER = ", "START = ", \
	"CPY = "};
	const char		*tab2[] = {"HERE", "APPEND", "IN", "OUT", "PIPE", "S_AND"\
	, "DIEZ", "END", "WORD", "CMD_SUFIX", "CMD", "CMD_NAME", "SIMPLE_COMMAND"\
	, "CMD_SUFFIX", "IO_REDIRECT", "IO_FILE", "IO_HERE", "FILENAME", "eof"\
	, "PIPE_SEQUENCE", "CMD_PREFIX", "NUMBER_OF_TOKENS"};
	const char		*tab[] = {"HERE", "APPEND", "IN", "OUT", "PIPE", "S_AND", \
	"DIEZ", "END", "WORD", "CMD_SUFFIX", "CMD", "CMD_NAME", "SIMPLE_COMMAND", \
	"CMD_SUFFIX", "IO_REDIRECT", "IO_FILE", "IO_HERE", "FILENAME", "eof", \
	"PIPE_SEQUENCE", "CMD_PREFIX", "OK"};

	ret_to_start(&head);
	printf("%s", str[whois]);
	while (head != NULL)
	{
		if (head->type >= 0 && head->type < NUMBER_OF_TOKENS \
		&& whois == 3)
			printf("%s=%s ", tab[head->type], head->str);
		else if (head->type >= 0 && head->type < NUMBER_OF_TOKENS \
		&& whois == 4)
			printf("%s ", tab2[head->type]);
		else if (head->type >= 0 && head->type < NUMBER_OF_TOKENS)
			printf("%s ", tab[head->type]);
		else
			printf("UNKNOWN ");
		head = head->next;
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
	if (str)
		token->str = ft_strdup(str);
	else
		token->str = NULL;
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
