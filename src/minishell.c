/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:10:24 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/09 13:54:25 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **ar, char **envp)
{
	t_env	*env;

	env = NULL;
	(void)ar;
	if (ac != 1)
		return (-1);
	make_env(&env, envp);
	prompt(&env);
	return (0);
}
