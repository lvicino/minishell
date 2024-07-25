/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:33:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/07/25 17:20:13 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_word(char *str, t_token **head, int c)
{
	int		start;
	char	*word;

	if (str[c] == '"')
	{
		c++;
		start = c;
		while (str[c] && str[c] != '"')
			c++;
	}
	else
	{
		start = c;
		while (ft_isalpha(str[c]))
			c++;
	}
	word = ft_substr(str, start, c - start);
	insert_token(head, WORD, word);
	if (str[c] == '"')
		c++;
	return (c);
}

t_token	*tokenize(char *str, t_token **head, int c)
{
	while (str[c])
	{
		if (str[c] == '>' && str[c + 1] == '>')
		{
			insert_token(head, APPEND, ">>");
			c++;
		}
		else if (str[c] == '>')
			insert_token(head, OUT, ">");
		else if (str[c] == '<' && str[c + 1] == '<')
		{
			insert_token(head, H_D, "<<");
			c++;
		}
		else if (str[c] == '<')
			insert_token(head, IN, "<");
		else if (str[c] == '|')
			insert_token(head, PIPE, "|");
		if (ft_isalpha(str[c]) || str[c] == '"' || str[c] == '/' \
		|| str[c] == '_' || str[c] == 39 || str[c] == '.')
			c = tokenize_word(str, head, c);
		else
			c++;
	}
	return (*head);
}

static int	bigger(char *str, char *exit)
{
	int	len_str;
	int	len_exit;

	len_str = ft_strlen(str);
	len_exit = ft_strlen(exit);
	if (len_str > len_exit)
		return (len_str);
	return (len_exit);
}

void parser(t_token *token, t_token *previous, t_token *current)
{
	if (current && current->type == WORD && (previous == NULL || previous->type == PIPE))
	{
		current->type = CMD;
		parser(token, previous, current);
		return ;
	}
	else if (current && current->type == WORD && previous && (previous->type == CMD || previous->type == CMD_SUFFIX))
	{
		current->type = CMD_SUFFIX;
		parser(token, previous, current);
		return ;
	}
	previous = current;
	if (current && current->next)
		current = current->next;
	if (current)
		parser(token, previous, current);
}

int	prompt(void)
{
	char	*str;
	char	*pr;
	t_token	*token;

	pr = ft_strjoin(getcwd(NULL, 0), "$ ");
	while (1)
	{
		token = NULL;
		str = readline(pr);
		if (!str || !ft_strncmp(str, "exit", bigger(str, "exit")))
			return (free(str), rl_clear_history(), ft_printf("exit\n"), 0);
		add_history(str);
		token = tokenize(str, &token, 0);
		print_tokens(token);
		parser(token, NULL, token);
		print_tokens(token);
		freelist(token);
		free(str);
	}
	return (0);
}
