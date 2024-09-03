/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:01:46 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/03 14:52:12 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_env **env, char **cmd, int cmd_ln)
{
	char		o_pwd[4096];
	char		n_pwd[4096];
	struct stat	path_stat;

	(void)env;
	if (cmd_ln > 2)
		return (ft_putstr_fd("Minishell : cd: Too many arguments\n", 2), 1);
	getcwd(o_pwd, 4096);
	if (cmd_ln > 0)
	{
		if (!stat(cmd[1], &path_stat))
		{
			if (!S_ISDIR(path_stat.st_mode))
				return (ft_putstr_fd("not a directory : ", 2), \
				ft_putstr_fd(cmd[1], 2), ft_putstr_fd("\n", 2), 1);
			else
			{
				chdir(cmd[1]);
				getcwd(n_pwd, 4096);
				printf("old pwd = %s$\n", o_pwd);
				printf("new pwd = %s$\n", n_pwd);
			}
		}
		else
			perror(cmd[0]);
	}
	return (0);
}
