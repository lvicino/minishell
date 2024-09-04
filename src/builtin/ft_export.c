/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:02:03 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/04 15:16:04 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_env(char *var, char *value, int r, t_env **env)
{
	(void)env;
	(void)r;
	printf("%s$\n", var);
	printf("%s$\n", value);
}

int	ft_export(t_env **env, char **cmd, int cmd_ln)
{
	int	r;
	int	i;
	int	j;
	int	start;

	(void)env;
	(void)cmd_ln;
	r = 0;
	i = 0;
	while (cmd[++i])
	{
		start = 0;
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '"' || cmd[i][j] == 39)
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(cmd[i],2 );
				ft_putstr_fd("': not a valid identifier\n", 2);
				r = 1;
				break;
			}
			if (cmd[i][j] == '=')
			{
				export_env(ft_substr(cmd[i], start, j), ft_substr(cmd[i], j + 1, ft_strlen(cmd[i]) - (j + 1)), r, env);
				break;
			}
			j++;
		}
	}
	return (r);
}
