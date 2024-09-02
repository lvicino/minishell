/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:01 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/02 15:50:58 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env **env, char **cmd, int cmd_ln)
{
	(void)cmd_ln;
	(void)env;
	printf("env cmd = %s$\n", cmd[0]);
	return (0);
}
