/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:10:24 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/21 16:25:43 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **ar, char **env)
{
	(void)ar;
	(void)env;
	if (ac != 1)
		return (-1);
	// make cpy env;
	prompt(env);
	return (0);
}
