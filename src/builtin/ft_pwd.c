/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:05 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/17 09:50:23 by rgallien         ###   ########.fr       */
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
