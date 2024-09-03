/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:13:30 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/02 23:09:48 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

typedef struct s_env
{
	char			*var;
	char			*value;
	struct	s_env	*prev;
	struct	s_env	*next;
}					t_env;

typedef struct s_builtin
{
	char	*fun;
	int	(*fun_ptr)(t_env **, char **, int);
}			t_builtin;

/*builtins*/
int	ft_cd(t_env **env, char **cmd, int cmd_ln);
int	ft_echo(t_env **env, char **cmd, int cmd_ln);

int		ft_env(t_env **env, char **cmd, int cmd_ln);
void	make_env(t_env **env, char **envp);
void	add_node(char *str, t_env **env, char *envp);
void	free_env(t_env **head);

int	ft_exit(t_env **env, char **cmd, int cmd_ln);
int	ft_export(t_env **env, char **cmd, int cmd_ln);
int	ft_pwd(t_env **env, char **cmd, int cmd_ln);
int	ft_unset(t_env **env, char **cmd, int cmd_ln);

#endif
