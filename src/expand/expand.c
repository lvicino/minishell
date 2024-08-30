/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 11:10:35 by rgallien          #+#    #+#             */
/*   Updated: 2024/08/30 12:52:30 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	expand_simple(char *str, char *new, int **tab)
{

}

void	ft_expand(t_token **cpy, t_env **env)
{
	char	*new;
	t_token	*current;
	int		tab[2];

	current = *cpy;
	while (current)
	{
		tab[0] = 0;
		tab[1] = 0;
		new = malloc((ft_count_expand(current->str, env) + 1) * sizeof(char));
		if (new)
			return (NULL);
		while (current->str[tab[0]])
		{
			if (current->str[tab[0]] == 39)
				expand_simple(current->str, new, &tab);
			else if (current->str[tab[0]] == '"')
				expand_double(current->str, new, &tab, env);
			else if (current->str[tab[0]] == '$')
				found_variable(current->str, new, &tab, env);
			else
				new[tab[1]] = current->str[tab[0]];
			tab[0]++;
		}
	}
}
*/
