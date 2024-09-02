/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:50:11 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/02 14:13:08 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	w_error(char *cmd, int error)
{
	if (error == 127 && (!cmd || !ft_strchr(cmd, '/')))
	{
		if (cmd)
			write(2, cmd, ft_strlen(cmd));
		else
			write(2, "''", 2);
		write(2, ": command not found", 19);
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

void	check_cmd_error(char **cmd, char *path, int *r) //! check if cmd is a directory ex : ../ ./ ./src src/ (maybe .)
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
