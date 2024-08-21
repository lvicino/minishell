/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 16:50:11 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/16 16:50:14 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	w_error(char *cmd, int error)
{
	if (error == 127 && (!cmd || !ft_strchr(cmd, '/')))
	{
		write(2, "Command '", 9);
		if (cmd)
			write(2, cmd, ft_strlen(cmd));
		write(2, "' not found", 11);
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

void	check_file_perm(int id, int m_id, char **argv, int *r)
{
	int	doc;

	doc = 0;
	if (!ft_strncmp(argv[1], "here_doc", 9))
		doc = 1;
	if (!doc && !id && access(argv[1], F_OK))
	{
		*r = 0;
		if (argv[1])
			write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": No such file or directory\n", 28);
	}
	else if (!doc && !id && access(argv[1], R_OK))
	{
		*r = 1;
		w_error(argv[1], 1);
	}
	else if (id == m_id && access(argv[m_id + 3 + doc], W_OK))
	{
		*r = 1;
		w_error(argv[m_id + 3 + doc], 1);
	}
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
