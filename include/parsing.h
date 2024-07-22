/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:12:31 by lvicino           #+#    #+#             */
/*   Updated: 2024/07/22 16:43:25 by rgallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum s_token_type
{
	WORD,
	IN,
	H_D,
	OUT,
	APPEND,
	PIPE
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*str;
	struct s_token		*next;
}				t_token;

int		prompt(void);
void	freelist(t_token *head);
void	print_tokens(t_token *head);
void	insert_token(t_token **head, t_token_type type, char *str);

#endif
