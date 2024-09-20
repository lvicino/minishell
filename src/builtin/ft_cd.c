/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:01:46 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/20 12:07:39 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_s_pwd(t_env **env, char *new)
{
	t_env	*current;

	current = *env;
	while (current && ft_strncmp(current->var, "S_PWD", \
	bigger(current->var, "S_PWD")))
		current = current->next;
	if (current)
	{
		if (current->value && new)
		{
			free(current->value);
			current->value = new;
		}
	}
}

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
		change_s_pwd(env, ft_strdup(current->value));
	}
	else
		free(n_pwd);
	current = *env;
	while (current && ft_strncmp(current->var, "OLDPWD", \
	bigger(current->var, "OLDPWD")))
		current = current->next;
	if (current)
	{
		free(current->value);
		current->value = o_pwd;
	}
	else
		free(o_pwd);
}

int	ft_cd_without_args(t_env *env)
{
	char		*o_pwd;
	char		*n_pwd;
	struct stat	path_stat;

	while (env && ft_strncmp(env->var, "HOME", bigger(env->var, "HOME")))
		env = env->next;
	if (!env)
		return (ft_putstr_fd("bash: cd: HOME not set\n", 1), 1);
	o_pwd = return_allocate();
	n_pwd = return_allocate();
	getcwd(o_pwd, 4096);
	if (!stat(env->value, &path_stat))
	{
		if (!S_ISDIR(path_stat.st_mode))
			return (ft_putstr_fd(env->value, 2), \
			ft_putstr_fd(": not a directory\n", 2), 1);
		else
			return (chdir(env->value), getcwd(n_pwd, 4096), \
			replace_pwd(n_pwd, o_pwd, &env), 0);
	}
	else
		return (perror(env->value), 1);
	return (1);
}

int	ft_cd(t_env **env, char **cmd, int cmd_ln, int fd)
{
	char		*o_pwd;
	char		*n_pwd;
	struct stat	path_stat;

	if (cmd_ln > 2)
		return (ft_putstr_fd("Minishell : cd: too many arguments\n", 2), 1);
	else if (cmd_ln == 1)
		return (ft_cd_without_args(*env));
	o_pwd = return_allocate();
	n_pwd = return_allocate();
	getcwd(o_pwd, 4096);
	if (!stat(cmd[1], &path_stat))
	{
		if (!S_ISDIR(path_stat.st_mode))
			return (free(o_pwd), free(n_pwd), ft_putstr_fd(cmd[1], 2), \
			ft_putstr_fd(": not a directory\n", 2), 1);
		else if (!chdir(cmd[1]) && getcwd(n_pwd, 4096))
			return (replace_pwd(n_pwd, o_pwd, env), 0);
		else if (cmd && cmd[1])
			return (ft_putstr_fd("cd: error retrieving current directory:", 2), \
			ft_putstr_fd(" getcwd: cannot access parent directories:", 2), \
			ft_putstr_fd(" No such file or directory\n", 2), \
			free(o_pwd), free(n_pwd), 1);
	}
	return ((void)fd, free(o_pwd), free(n_pwd), perror(cmd[0]), 1);
}
