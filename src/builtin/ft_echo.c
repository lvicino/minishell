/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:01:51 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/02 23:36:37 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_env **env, char **cmd, int cmd_ln)
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
		printf("%s", cmd[i]);
		if (i + 1 < cmd_ln)
			printf(" ");
		i++;
	}
	if (!active)
		printf("\n");
	return (0);
}
