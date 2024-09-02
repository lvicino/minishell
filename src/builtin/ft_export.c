/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:03 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/02 15:51:12 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_env **env, char **cmd, int cmd_ln)
{
	(void)cmd_ln;
	(void)env;
	printf("export cmd = %s$\n", cmd[0]);
	return (0);
}
