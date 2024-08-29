/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:39:23 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/29 15:43:30 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bigger(char *s1, char *s2)
{
	int	a;
	int	b;

	a = ft_strlen(s1);
	b = ft_strlen(s2);
	if (a > b)
		return (a);
	return (b);
}

int	found_variable(char *str, int *i, t_env **env)
{
	int		start;
	int		end;
	char	*var2;
	t_env	*current;

	current = *env;
	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != '$' && str[*i] != '"')
		(*i)++;
	end = *i - start;
	var2 = ft_substr(str, start, end);
	while (current)
	{
		if (!ft_strncmp(current->var, var2, bigger(current->var, var2)))
			return (ft_printf("%s\n", current->value), free(var2), ft_strlen(current->value));
		current = current->next;
	}
	return (0);
}

int	expand_double(char *str, int *i, t_env **env)
{
	int	c;

	c = 0;
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			c += found_variable(str, i, env);
		(*i)++;
	}
	return (c);
}

int	expand_simple(char *str, int	*i)
{
	int	c;

	c = 0;
	(*i)++;
	while (str[*i] && str[*i] != 39)
	{
		(*i)++;
		c++;
	}
	c--;
	return (c);
}

t_token	*ft_expand(t_token **cpy, t_env **env)
{
	t_token	*current;
	int		i;
	int		c;

	current = *cpy;
	while (current->type != END)
	{
		c = 0;
		i = 0;
		printf("%s=", current->str);
		while (current->str[i])
		{
			if (current->str[i] == 39)
				c += expand_simple(current->str, &i);
			else if (current->str[i] == '"')
				c += expand_double(current->str, &i, env);
			else
				c++;
			i++;
		}
		printf("%d\n", c);
		current = current->next;
	}
	return (*cpy);
}
