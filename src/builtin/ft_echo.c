/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:01:51 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/02 15:50:53 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_env **env, char **cmd, int cmd_ln)
{
	(void)cmd_ln;
	(void)env;
	printf("echo cmd = %s$\n", cmd[0]);
	return (0);
}
