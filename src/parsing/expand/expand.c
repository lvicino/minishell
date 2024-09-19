/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:10:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/19 12:01:19 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	found_variable(char *str, char *new, int *tab, t_env *current)
{
	int		start;
	int		end;
	char	*var;

	tab[0]++;
	start = tab[0];
	while (str[tab[0]] && str[tab[0]] != '"' && str[tab[0]] != 39 && \
	str[tab[0]] != '$' && str[tab[0]] != '?' && !ft_isspace(str[tab[0]]))
		tab[0]++;
	if (str[tab[0]] == '?' && tab[0] && str[tab[0] - 1] == '$')
		tab[0]++;
	end = tab[0] - start;
	var = ft_substr(str, start, end);
	while (current)
	{
		if (found_variable_aux(&current, new, tab, var))
			return ;
		current = current->next;
	}
	free(var);
}

void	expand_simple(char *str, char *new, int *tab)
{
	tab[0]++;
	while (str[tab[0]] && str[tab[0]] != 39)
	{
		new[tab[1]] = str[tab[0]];
		tab[0]++;
		tab[1]++;
	}
	if (str[tab[0]] == 39)
		tab[0]++;
}

void	expand_double(char *str, char *new, int *tab, t_env **env)
{
	tab[0]++;
	while (str[tab[0]] && str[tab[0]] != '"')
	{
		if (str[tab[0]] == '$')
		{
			if (!str[tab[0] + 1] || ft_isspace(str[tab[0] + 1]) \
			|| str[tab[0] + 1] == '"' || str[tab[0] + 1] == 39)
			{
				new[tab[1]] = '$';
				tab[1]++;
				tab[0]++;
			}
			else
				found_variable(str, new, tab, *env);
		}
		else
		{
			new[tab[1]] = str[tab[0]];
			tab[1]++;
			tab[0]++;
		}
	}
	if (str[tab[0] == '"'])
		tab[0]++;
}

t_token	*end_and_next(t_token *current, char *new, int *tab)
{
	new[tab[1]] = 0;
	if (!ft_strlen(new) && !ft_strchr(current->str, 39) && \
	!ft_strchr(current->str, '"') && is_not_filename(current))
		free_node(&current, new);
	else if (current && current->str && !current->ambiguous)
	{
		free(current->str);
		current->str = new;
		if (current->type == HERE)
			current = current->next;
		current = current->next;
	}
	return (current);
}

void	ft_expand(t_token **cpy, t_env **env)
{
	char	*new;
	t_token	*current;
	int		tab[2];

	current = *cpy;
	while (current && current->type != END)
	{
		tab[0] = 0;
		tab[1] = 0;
		new = malloc((ft_count_expand(current->str, env) + 1) * sizeof(char));
		if (!new)
			return ;
		while (current->str[tab[0]])
		{
			if (current->str[tab[0]] == 39)
				expand_simple(current->str, new, tab);
			else if (current->str[tab[0]] == '"')
				expand_double(current->str, new, tab, env);
			else
				ft_expand_aux(&current, tab, env, new);
		}
		current = end_and_next(current, new, tab);
	}
	ret_to_start(&current);
	*cpy = current;
}
