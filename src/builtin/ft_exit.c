/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:02 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/05 16:09:42 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_env **env, char **cmd, int cmd_ln)
{
	(void)env;
	if (cmd_ln > 1)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": unrecognized option '", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("' \n", 2);
		exit(2);
	}
	exit(0);
	return (0);
}
