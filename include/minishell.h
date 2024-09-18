/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:13:06 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/18 16:36:11 by rgallien         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

void	sigint_handler_hd(int signal);
void	sigint_handler_prompt(int signal);
void	sigint_handler_parent(int signal);
void	get_exit_value(int value, t_env **env);
void	initial_signal(void);
void	signal_child(void);
void	signal_hd(void);
void	signal_parent(void);

#endif
