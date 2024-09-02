/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:50:11 by lvicino           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/01 16:29:57 by rgallien         ###   ########.fr       */
=======
/*   Updated: 2024/08/30 15:21:45 by lvicino          ###   ########.fr       */
>>>>>>> origin/lvicino
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	w_error(char *cmd, int error)
{
	if (error == 127 && (!cmd || !ft_strchr(cmd, '/')))
	{
		write(2, "Command ", 9);
		if (cmd)
			write(2, cmd, ft_strlen(cmd));
		write(2, " not found", 11);
	}
	else if (error == 127)
	{
		if (cmd)
			write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory", 27);
	}
	else if (error == 126 || error == 1)
	{
		if (cmd)
			write(2, cmd, ft_strlen(cmd));
		write(2, ": Permission denied", 19);
	}
	write(2, "\n", 1);
}

void	check_cmd_error(char **cmd, char *path, int *r)
{
	if (!path || access(path, F_OK))
	{
		*r = 127;
		if (cmd && cmd[0])
			w_error(cmd[0], 127);
		else
			w_error(NULL, 127);
	}
	else if (!access(path, F_OK) && access(path, X_OK))
	{
		*r = 126;
		if (cmd && cmd[0])
			w_error(cmd[0], 126);
		else
			w_error(NULL, 126);
	}
}
