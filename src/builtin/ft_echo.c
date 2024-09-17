/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:01:51 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/12 17:02:37 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_env **env, char **cmd, int cmd_ln, int fd)
{
	int	i;
	int	j;
	int	active;

	i = 0;
	active = 0;
	while (cmd[++i] && cmd[i][0] == '-')
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (!cmd[i][j])
			active = 1;
		else
			break;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (i++ + 1 < cmd_ln)
			ft_putstr_fd(" ", fd);
	}
	if (!active)
		ft_putstr_fd("\n", fd);
	return ((void)env, 0);
}
