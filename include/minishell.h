/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:11:09 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/22 15:14:50 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define _XOPEN_SOURCE 700

# include "libft.h"

# include "builtin.h"
# include "exec.h"
# include "parsing.h"
# include <signal.h>

# include <stdio.h>
# include <stdbool.h>


# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
// # include <string.h>
// # include <error.h>

#endif
