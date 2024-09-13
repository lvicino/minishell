/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:51:07 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/13 01:34:09 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_aux(t_token **current, int *tab, t_env **env, char *new)
{
	if ((*current)->str[tab[0]] == '$' && (!(*current)->str[tab[0] + 1] \
	|| ft_isspace((*current)->str[tab[0] + 1])))
	{
		new[tab[1]] = '$';
		tab[0]++;
		tab[1]++;
	}
	else if ((*current)->str[tab[0]] == '$')
		found_variable((*current)->str, new, tab, *env);
	else
	{
		new[tab[1]] = (*current)->str[tab[0]];
		tab[0]++;
		tab[1]++;
	}
}

int	found_variable_aux(t_env **current, char *new, int *tab, char *var)
{
	int	i;

	if (!ft_strncmp((*current)->var, var, bigger((*current)->var, var)))
	{
		i = 0;
		while ((*current)->value[i])
		{
			new[tab[1]] = (*current)->value[i];
			i++;
			tab[1]++;
		}
		free(var);
		return (1);
	}
	return (0);
}
