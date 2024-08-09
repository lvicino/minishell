/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubengallien <rubengallien@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:33:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/09 13:23:24 by rubengallie      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	automate(t_token **buffer)
{
	t_token	*stack;

	stack = NULL;
	state_0(buffer, &stack);
}

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

int	is_token(char *str, const char **list, int *c, int *i)
{
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

t_token	*tokenize(char *str, t_token **head, int c)
{
	const char	*list[] = {"<<", ">>", "<", ">", "|", "&", "#"};
	int			i;

	while (str[c])
	{
		i = 0;
		if (is_token(str, list, &c, &i))
			insert_token(head, i, (char *)list[i]);
		else if (is_word(str[c]))
			c = tokenize_word(str, head, c);
		else
			c++;
	}
	return (*head);
}

int	prompt(void)
{
	char	*str;
	t_token	*token;
	t_token	*stack;

	while (1)
	{
		token = NULL;
		str = readline(">> ");
		if (!str || !ft_strncmp(str, "exit", bigger(str, "exit")))
			return (free(str), clear_history(), ft_printf("exit\n"), 0);
		add_history(str);
		token = tokenize(str, &token, 0);
		insert_token(&token, END, NULL);
		print_tokens(token, 3);
		stack = NULL;
		state_0(&token, &stack);
		freelist(token);
		free(str);
	}
	return (0);
}
