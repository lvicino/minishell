/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:01:51 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/09 17:01:39 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_env **env, char **cmd, int cmd_ln, int fd)
{
	int	i;
	int	active;

	i = 1;
	active = 0;
	(void)env;
	while (cmd && cmd[i] && !ft_strncmp(cmd[i], "-n", bigger(cmd[i], "-n")))
	{
		active = 1;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], fd);
		if (i + 1 < cmd_ln)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!active)
		ft_putstr_fd("\n", fd);
	return (0);
}
