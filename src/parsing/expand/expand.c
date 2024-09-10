/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:10:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/10 16:10:24 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	found_variable(char *str, char *new, int *tab, t_env *current)
{
	int		start;
	int		end;
	char	*var;
	int		i;

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
		if (!ft_strncmp(current->var, var, bigger(current->var, var)))
		{
			i = 0;
			while (current->value[i])
			{
				new[tab[1]] = current->value[i];
				i++;
				tab[1]++;
			}
			free(var);
			return ;
		}
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
			else if (current->str[tab[0]] == '$' && (!current->str[tab[0] + 1] \
			|| ft_isspace(current->str[tab[0] + 1])))
			{
				new[tab[1]] = '$';
				tab[0]++;
				tab[1]++;
			}
			else if (current->str[tab[0]] == '$')
				found_variable(current->str, new, tab, *env);
			else
			{
				new[tab[1]] = current->str[tab[0]];
				tab[0]++;
				tab[1]++;
			}
		}
		new[tab[1]] = 0;
		if (!(ft_strlen(new) && (ft_strchr(current->str, 39) || ft_strchr(current->str, '"'))))
			free_node(&current, new);
		else if (current && current->str)
		{
			free(current->str);
			current->str = new;
			current = current->next;
		}
	}
	ret_to_start(&current);
	*cpy = current;
}
