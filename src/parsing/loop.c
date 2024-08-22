/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:33:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/22 12:36:00 by rgallien         ###   ########.fr       */
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

void	tokenize_cpy(t_token *tmp, int i)
{
	while (tmp)
	{
		if (!i && tmp->type == WORD && (!tmp->prev || tmp->prev->type == PIPE \
		|| tmp->prev->type == FILENAME))
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
		while (str[c] && !is_token(str, &c, i) && !ft_isspace(str[c]))
			c++;
	}
	word = ft_substr(str, start, c - start);
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
			c = tokenize_word(str, head, c, &i);
	}
	return (*head);
}

int	prompt(t_env	**env)
{
	char	*str;
	t_token	*token;
	t_token	*stack;
	t_token	*cpy;

	(void)env;
	while (1)
	{
		token = NULL;
		cpy = NULL;
		str = readline(">> ");
		if (!str || !ft_strncmp(str, "exit", bigger(str, "exit")))
			return (free(str), clear_history(), ft_printf("exit\n"), 0);
		add_history(str);
		token = tokenize(str, &token, 0);
		cpy = tokenize(str, &cpy, 0);
		tokenize_cpy(cpy, 0);
		insert_token(&token, END, NULL);
		print_tokens(token, 2);
		stack = NULL;
		state_0(&token, &stack);
		freelist(&cpy);
		freelist(&stack);
		//exec(cpy, env);
		free(str);
	}
}
