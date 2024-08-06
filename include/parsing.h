/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:12:31 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/06 15:46:51 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum s_token_type
{
	HERE,
	APPEND,
	IN,
	OUT,
	PIPE,
	S_AND,
	DIEZ,
	END,
	WORD,
	CMD_SUFIX,
	CMD,
	SIMPLE_COMMAND,
	CMD_SUFFIX,
	IO_REDIRECT,
	IO_FILE,
	IO_HERE,
	FILENAME,
	EOF,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*str;
	struct s_token		*next;
}				t_token;

int	bigger(char *s1, char *s2);
int		prompt(void);
void	freelist(t_token *head);
void	print_tokens(t_token *head);
void	insert_token(t_token **head, t_token_type type, char *str);

#endif
