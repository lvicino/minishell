/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:51:07 by rgallien          #+#    #+#             */
/*   Updated: 2024/09/12 16:01:06 by rgallien         ###   ########.fr       */
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