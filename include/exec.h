/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:14:05 by lvicino           #+#    #+#             */
/*   Updated: 2024/09/07 18:31:07 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_cmd
{
	int		in;
	int		out;
	char	*path;
	char	**cmd;
}			t_cmd;

typedef struct s_info
{
	int		id;
	int		r;
	pid_t	pid;
	int		n_pipe;
	int		n_here;
	int		cmd_ln;
	int		**fd;
	int		**here;
	int		skip_hd;
	int		builtin;
	t_cmd	cmd;
}			t_info;

/*exec*/
int	exec(t_token **token, t_env **env);
int	exec_builtin(t_info *var, t_env **env);

/*utils*/
void	count_pipe(t_info *input, t_token *token);
int		wait_process(pid_t pid, int id, int *r);
void	ft_free(char ***str);
void	free_pipeline(int ***fd, int i);
int		pipeline(int ***tab, int n);

/*here_doc*/
void	make_doc(t_info	*var, t_token *token);

/*pipeline*/
int		choose_pipe(t_info	*var, t_token **token);
int		choose_in_out(t_info *var, t_token *token);

/*get cmd*/
void	get_cmd(t_token *token, t_info *var);
char	*get_path(char *cmd, t_env *env);

/*error*/
void	w_error(char *cmd, int error);
void	check_cmd_error(char **cmd, char *path, int *r);
int		check_file_perm(t_info *var, t_token *token);

#endif
