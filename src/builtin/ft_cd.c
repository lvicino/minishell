/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:01:46 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/07 18:02:22 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_allocate(void)
{
	char	*pwd;

	pwd = malloc(sizeof(char) * 4096);
	if (!pwd)
		return (NULL);
	return (pwd);
}

void	replace_pwd(char *n_pwd, char *o_pwd, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current && ft_strncmp(current->var, "PWD", \
	bigger(current->var, "PWD")))
		current = current->next;
	if (current)
	{
		free(current->value);
		current->value = n_pwd;
	}
	current = *env;
	while (current && ft_strncmp(current->var, "OLDPWD", \
	bigger(current->var, "OLDPWD")))
		current = current->next;
	if (current)
	{
		free(current->value);
		current->value = o_pwd;
	}
}

int	ft_cd(t_env **env, char **cmd, int cmd_ln)
{
	char		*o_pwd;
	char		*n_pwd;
	struct stat	path_stat;

	(void)env;
	if (cmd_ln > 2)
		return (ft_putstr_fd("Minishell : cd: Too many arguments\n", 2), 1);
	o_pwd = return_allocate();
	n_pwd = return_allocate();
	getcwd(o_pwd, 4096);
	if (cmd_ln > 0)
	{
		if (!stat(cmd[1], &path_stat))
		{
			if (!S_ISDIR(path_stat.st_mode))
				return (ft_putstr_fd(cmd[1], 2), \
				ft_putstr_fd(": not a directory", 2), ft_putstr_fd("\n", 2), 1);
			else
				return (chdir(cmd[1]), getcwd(n_pwd, 4096), \
				replace_pwd(n_pwd, o_pwd, env), 0);
		}
		else
			return (perror(cmd[0]), 1);
	}
	return (1);
}
