/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:13:06 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/01 19:53:00 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

# include "libft.h"

# include "builtin.h"
# include "parsing.h"
# include "exec.h"
# include <stdio.h>
# include <stdbool.h>


# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
// # include <string.h>
// # include <error.h>

void	set_signal_action(void);

#endif
