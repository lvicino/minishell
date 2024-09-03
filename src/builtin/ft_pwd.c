/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:05 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/03 15:36:24 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env **env, char **cmd, int cmd_ln)
{
	char	path[4096];

	(void)env;
	(void)cmd;
	(void)cmd_ln;
	if (!getcwd(path, 4096))
	 	printf("getcwd() error\n");
	else
		printf("%s\n", path);
	return (0);
}
