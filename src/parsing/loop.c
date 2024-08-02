/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:33:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/02 15:11:00 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_word(char *str, t_token **head, int c)
{
	int		start;
	char	*word;

	if (str[c] == '"' || str[c] == 39)
	{
		c++;
		start = c;
		while (str[c] && str[c] != '"')
			c++;
	}
	else
	{
		start = c;
		while (ft_isalpha(str[c]) || str[c] == '/' \
		|| str[c] == '_' || str[c] == '.')
			c++;
	}
	word = ft_substr(str, start, c - start);
	if (str[c] == '"' || str[c] == 39)
		c++;
	return (insert_token(head, WORD, word), free(word), c);
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
			insert_token(head, HERE, "<<");
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

// void parser(t_token *tokens)
// {
// 	t_token *stack;
// 	t_token *first;

// 	stack = NULL;
// }

int	prompt(void)
{
	char	*str;
	t_token	*token;

	while (1)
	{
		token = NULL;
		str = readline(">> ");
		if (!str || !ft_strncmp(str, "exit", bigger(str, "exit")))
			return (free(str), rl_clear_history(), ft_printf("exit\n"), 0);
		add_history(str);
		token = tokenize(str, &token, 0);
		insert_token(&token, END, NULL);
		print_tokens(token);
		// parser(token);
		// print_tokens(token);
		freelist(token);
		free(str);
	}
	return (0);
}
