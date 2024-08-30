/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:10:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/30 17:04:47 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	found_variable(char *str, char *new, int *tab, t_env **env)
{
	int		start;
	int		end;
	t_env	*current;
	char	*var;
	int		i;

	current = *env;
	tab[0]++;
	start = tab[0];
	while (str[tab[0]] && str[tab[0]] != '"')
		tab[0]++;
	printf("tab[0] = %d\n", tab[0]);
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
			new[tab[1]] = 0;
			free(var);
			printf("tab[1] = %d\n", tab[1]);
			return ;
		}
		current = current->next;
	}
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
}

void	expand_double(char *str, char *new, int *tab, t_env **env)
{
	tab[0]++;
	while (str[tab[0]] && str[tab[0]] != '"')
	{
		if (str[tab[0]] == '$')
			found_variable(str, new, tab, env);
		else
			new[tab[1]] = str[tab[0]];
		tab[0]++;
		tab[1]++;
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
		printf("current str = %s\n", current->str);
		new = malloc((ft_count_expand(current->str, env) + 1) * sizeof(char));
		printf("malloc de %d\n", ft_count_expand(current->str, env) + 1);
		if (!new)
			return ;
		while (current->str[tab[0]])
		{
			if (current->str[tab[0]] == 39)
				expand_simple(current->str, new, tab);
			else if (current->str[tab[0]] == '"')
				expand_double(current->str, new, tab, env);
			else if (current->str[tab[0]] == '$')
				found_variable(current->str, new, tab, env);
			else
			{
				new[tab[1]] = current->str[tab[0]];
				tab[0]++;
				tab[1]++;
			}

		}
		printf("tab[1] = %d\n", tab[1]);
		free(current->str);
		current->str = new;
		printf("%s$\n", current->str);
		current = current->next;
	}
}

