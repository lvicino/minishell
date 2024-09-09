/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:05 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/09 18:39:01 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env **env, char **cmd, int cmd_ln, int fd)
{
	char	path[4096];

	(void)env;
	(void)cmd;
	(void)cmd_ln;
	if (!getcwd(path, 4096))
		ft_putstr_fd("getcwd() error\n", 2);
	else
	{
		ft_putstr_fd(path, fd);
		ft_putstr_fd("\n", fd);
	}
	return (0);
}
