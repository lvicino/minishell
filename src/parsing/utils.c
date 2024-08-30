/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:49:07 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/28 16:56:53 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char *str, int *c, int *i)
{
	const char	*list[] = {"<<", ">>", "<", ">", "|", "&", "#"};

	*i = 0;
	while (*i < END)
	{
		if (!ft_strncmp(str + *c, list[*i], ft_strlen(list[*i])))
		{
			*c += ft_strlen(list[*i]);
			return (1);
		}
		(*i)++;
	}
	return (0);
}

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

void	freelist(t_token **head)
{
	t_token	*tmp;

	if (head == NULL || *head == NULL)
		return ;
	ret_to_start(head);
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->str);
		free(tmp);
	}
}

void	print_tokens(t_token *head, int whois)
{
	const char		*str[5] = {"RIEN", "STACK = ", "BUFFER = ", "START = ", \
	"CPY = "};
	const char		*tab2[] = {"HERE", "APPEND", "IN", "OUT", "PIPE", "S_AND"\
	, "DIEZ", "END", "WORD", "CMD_SUFIX", "CMD", "CMD_NAME", "SIMPLE_COMMAND"\
	, "CMD_SUFFIX", "IO_REDIRECT", "IO_FILE", "IO_HERE", "FILENAME", "END_F"\
	, "PIPE_SEQUENCE", "CMD_PREFIX", "NUMBER_OF_TOKENS"};
	const char		*tab[] = {"HERE", "APPEND", "IN", "OUT", "PIPE", "S_AND", \
	"DIEZ", "END", "WORD", "CMD_SUFFIX", "CMD", "CMD_NAME", "SIMPLE_COMMAND", \
	"CMD_SUFFIX", "IO_REDIRECT", "IO_FILE", "IO_HERE", "FILENAME", "END_F", \
	"PIPE_SEQUENCE", "CMD_PREFIX", "OK"};

	ret_to_start(&head);
	printf("%s", str[whois]);
	while (head != NULL)
	{
		if (head->type >= 0 && head->type < NUMBER_OF_TOKENS \
		&& whois == 3)
			printf("%s=%s$ ", tab[head->type], head->str);
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

