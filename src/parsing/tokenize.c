/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:01:23 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/30 13:45:18 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quotes(t_token *token)
{
	int		i;
	char	q;

	while (token)
	{
		i = 0;
		while (token->str && token->str[i])
		{
			if (token->str[i] == '"' || token->str[i] == 39)
			{
				q = token->str[i];
				i++;
				while (token->str[i] && token->str[i] != q)
					i++;
				if (!token->str[i])
					return (ft_putstr_fd("Error, Unclosed quotes\n", 2), 0);
			}
			i++;
		}
		token = token->next;
	}
	return (1);
}

void	tokenize_cpy(t_token *tmp, int i)
{
	while (tmp)
	{
		if (!i && tmp->type == WORD && (!tmp->prev || tmp->prev->type == PIPE \
		|| tmp->prev->type == FILENAME || tmp->prev->type == END_F))
		{
			i = 1;
			tmp->type = CMD;
		}
		else if (i && tmp->type == WORD && tmp->prev && (tmp->prev->type \
		== CMD || tmp->prev->type == CMD_SUFFIX || tmp->prev->type == FILENAME \
		|| tmp->prev->type == END_F))
			tmp->type = CMD_SUFFIX;
		else if (tmp->type == WORD && tmp->prev && (tmp->prev->type == IN || \
		tmp->prev->type == APPEND || tmp->prev->type == OUT))
			tmp->type = FILENAME;
		else if (tmp->type == WORD && tmp->prev && tmp->prev->type == HERE)
			tmp->type = END_F;
		else if (tmp->type == PIPE)
			i = 0;
		tmp = tmp->next;
	}
}

int	tokenize_word(char *str, t_token **head, int c, int *i)
{
	int		start;
	char	*word;
	char	b;

	if (str[c] == '"' || str[c] == 39)
	{
		b = str[c];
		start = c;
		c++;
		while (str[c] && str[c] != b)
			c++;
	}
	else
	{
		start = c;
		while (str[c] && !is_token(str, &c, i) && !ft_isspace(str[c + 1]))
			c++;
	}
	word = ft_substr(str, start, (c - start) + 1);
	if (str[c] && ft_isspace(str[c + 1]))
		c++;
	if (str[c] == '"' || str[c] == 39)
		c++;
	return (insert_token(head, WORD, word), free(word), c);
}

t_token	*tokenize(char *str, t_token **head, int c)
{
	int			i;
	const char	*list[] = {"<<", ">>", "<", ">", "|", "&", "#"};

	while (str[c])
	{
		i = 0;
		while (ft_isspace(str[c]))
			c++;
		if (is_token(str, &c, &i))
			insert_token(head, i, (char *)list[i]);
		else
		{
			c = tokenize_word(str, head, c, &i);
			if (c == -1)
				return (NULL);
		}
	}
	insert_token(head, END, NULL);
	return (*head);
}

int	make_tokenize(t_token **token, t_token **stack, t_token **cpy, char *str)
{
	*token = NULL;
	*cpy = NULL;
	if (!ft_strlen(str))
		return (0);
	*token = tokenize(str, token, 0);
	if (!(*token))
		return (0);
	if (!unclosed_quotes(*token))
		return (freelist(token), 0);
	*cpy = tokenize(str, cpy, 0);
	tokenize_cpy(*cpy, 0);
	*stack = NULL;
	return (1);
}
