/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:06 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/02 15:51:26 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env **env, char **cmd, int cmd_ln)
{
	(void)cmd_ln;
	(void)env;
	printf("unset cmd = %s$\n", cmd[0]);
	return (0);
}
