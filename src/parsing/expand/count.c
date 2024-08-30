/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:39:23 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/30 14:29:31 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_found_variable(char *str, int *i, t_env **env)
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
			return (free(var2), ft_strlen(current->value));
		current = current->next;
	}
	return (0);
}


int	count_expand_double(char *str, int *i, t_env **env)
{
	int	c;

	c = 0;
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			c += count_found_variable(str, i, env);
		else
			c++;
		(*i)++;
	}
	return (c);
}

int	count_expand_simple(char *str, int	*i)
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

int	ft_count_expand(char *str, t_env **env)
{
	int		i;
	int		c;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
			c += count_expand_simple(str, &i);
		else if (str[i] == '"')
			c += count_expand_double(str, &i, env);
		else if (str[i] == '$')
			c += count_found_variable(str, &i, env);
		else
			c++;
		i++;
	}
	return (c);
}
