/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:05 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/20 12:02:20 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_s_pwd(t_env **env)
{
	t_env	*current;

	current = *env;
	while (current && ft_strncmp(current->var, "S_PWD", \
	bigger(current->var, "S_PWD")))
		current = current->next;
	if (current)
		return (current->value);
	else
		return (NULL);
}

int	ft_pwd(t_env **env, char **cmd, int cmd_ln, int fd)
{
	char	path[4096];

	(void)env;
	(void)cmd;
	(void)cmd_ln;
	if (!getcwd(path, 4096))
	{
		ft_putstr_fd(print_s_pwd(env), fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		ft_putstr_fd(path, fd);
		ft_putstr_fd("\n", fd);
	}
	return (0);
}
