/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:02 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/18 17:20:37 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_env **env, char **cmd, int cmd_ln, int fd)
{
	int	i;

	(free_env(env), (void)fd);
	i = -1;
	while (cmd[1] && cmd[1][++i])
	{
		if ((!ft_isdigit(cmd[1][i]) && (cmd[1][0] != '-' && \
		cmd[1][0] != '+')) || (!i && (((cmd[1][0] == '-' || \
		cmd[1][0] == '+') && ft_strlen(cmd[1]) > 21) || \
		ft_strlen(cmd[1]) > 20)))
		{
			(ft_putstr_fd("exit: ", 2), ft_putstr_fd(cmd[1], 2));
			(ft_putstr_fd(": numeric argument required\n", 2), exit(2));
		}
	}
	if (cmd_ln > 2)
		(ft_putstr_fd("exit: too many arguments\n", 2), exit(1));
	else if (cmd_ln > 1)
		return ((unsigned char)ft_atoi(cmd[1]));
	return (0);
}

int	ft_exit0(t_env **env, char **cmd, int cmd_ln, int fd)
{
	int	i;

	free_env(env);
	ft_putstr_fd("exit\n", fd);
	i = -1;
	while (cmd && cmd[1] && cmd[1][++i])
	{
		if ((!ft_isdigit(cmd[1][i]) && (cmd[1][0] != '-' && \
		cmd[1][0] != '+')) || (!i && (((cmd[1][0] == '-' || \
		cmd[1][0] == '+') && ft_strlen(cmd[1]) > 21) || \
		ft_strlen(cmd[1]) > 20)))
		{
			(ft_putstr_fd("exit: ", 2), ft_putstr_fd(cmd[1], 2));
			(ft_putstr_fd(": numeric argument required\n", 2), exit(2));
		}
	}
	if (cmd_ln > 2)
		(ft_putstr_fd("exit: too many arguments\n", 2), exit(1));
	else if (cmd_ln > 1)
		return ((unsigned char)ft_atoi(cmd[1]));
	return (0);
}
