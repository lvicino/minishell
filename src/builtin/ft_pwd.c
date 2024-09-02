/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:05 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/02 15:51:21 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env **env, char **cmd, int cmd_ln)
{
	(void)cmd_ln;
	(void)env;
	printf("pwd cmd = %s$\n", cmd[0]);
	return (0);
}
