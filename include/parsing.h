/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:12:31 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/21 16:05:06 by rgallien         ###   ########.fr       */
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
	CMD_NAME,
	SIMPLE_COMMAND,
	CMD_SUFFIX,
	IO_REDIRECT,
	IO_FILE,
	IO_HERE,
	FILENAME,
	END_F,
	PIPE_SEQUENCE,
	CMD_PREFIX,
	OK,
	NUMBER_OF_TOKENS,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*str;
	struct s_token		*next;
	struct s_token		*prev;
}				t_token;

typedef struct s_assoc
{
	t_token_type	type;
	void			(*func)(t_token **, t_token **);
}t_assoc;

void		ret_to_start(t_token **head);
int			ft_isspace(int c);
int			is_word(char c);
int			bigger(char *s1, char *s2);
int			prompt(char **env);
void		freelist(t_token **head);
void		print_tokens(t_token *head, int whois);
void		insert_token(t_token **head, t_token_type type, char *str);
// states
void		state_error(t_token **head, t_token **buffer);
int			state_0(t_token **buffer, t_token **stack);
void		state_1(t_token **buffer, t_token **head);
void		state_2(t_token **buffer, t_token **head);
void		state_3(t_token **buffer, t_token **head);
void		state_4(t_token **buffer, t_token **head);
void		state_5(t_token **buffer, t_token **head);
void		state_6(t_token **buffer, t_token **head);
void		state_7(t_token **buffer, t_token **head);
void		state_8(t_token **buffer, t_token **head);
void		state_9(t_token **buffer, t_token **head);
void		state_10(t_token **buffer, t_token **head);
void		state_11(t_token **buffer, t_token **head);
void		state_12(t_token **buffer, t_token **head);
void		state_13(t_token **buffer, t_token **head);
void		state_14(t_token **buffer, t_token **head);
void		state_15(t_token **buffer, t_token **head);
void		state_16(t_token **buffer, t_token **head);
void		state_17(t_token **buffer, t_token **head);
void		state_18(t_token **buffer, t_token **head);
void		state_19(t_token **buffer, t_token **head);
void		state_20(t_token **buffer, t_token **head);
void		state_21(t_token **buffer, t_token **head);
void		state_22(t_token **buffer, t_token **head);
void		state_23(t_token **buffer, t_token **head);
void		state_24(t_token **buffer, t_token **head);
void		state_25(t_token **buffer, t_token **head);
void		state_26(t_token **buffer, t_token **head);
void		state_27(t_token **buffer, t_token **head);
void		state_28(t_token **buffer, t_token **head);
void		state_29(t_token **buffer, t_token **head);
t_assoc		*get_tab(int state);
t_token		*add_to_stack(t_token **buffer, t_token **stack);
void		ft_del_token(t_token **lst, void (*del)(void*));
void		ft_del_token_test(t_token **head, void (*del)(void*));

#endif
