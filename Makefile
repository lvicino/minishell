# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 16:21:52 by lvicino           #+#    #+#              #
#    Updated: 2024/08/29 13:26:44 by rgallien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

LIBFT		=	libft/libft.a


BUILD_DIR	=	build


SRC_DIR		=	src

MAIN		=	minishell.c

MAIN		:=	$(MAIN:%=$(SRC_DIR)/%)
MAIN_OBJ	=	$(MAIN:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
MAIN_DEP	=	$(MAIN_OBJ:$(BUILD_DIR)/%.o=$(BUILD_DIR)/%.d)



BUILTIN_DIR	=	src/builtin

BUILTIN		=

BUILTIN		:=	$(BUILTIN:%=$(BUILTIN_DIR)/%)
BUILTIN_OBJ	=	$(BUILTIN:$(BUILTIN_DIR)/%.c=$(BUILD_DIR)/%.o)
BUILTIN_DEP	=	$(BUILTIN_OBJ:$(BUILD_DIR)/%.o=$(BUILD_DIR)/%.d)



EXEC_DIR	=	src/exec

EXEC		=	exec.c \
				exec_utils.c \
				choose_pipe.c \
				here_doc.c \
				error.c \
				get_cmd.c


EXEC		:=	$(EXEC:%=$(EXEC_DIR)/%)
EXEC_OBJ	=	$(EXEC:$(EXEC_DIR)/%.c=$(BUILD_DIR)/%.o)
EXEC_DEP			=	$(EXEC_OBJ:$(BUILD_DIR)/%.o=$(BUILD_DIR)/%.d)



PARSING_DIR	=	src/parsing

PARSING		=	state/state.c \
				loop.c \
				utils.c \
				state/state_utils.c \
				state/state_1_5.c \
				state/state_6_10.c \
				state/state_11_15.c \
				state/state_16_20.c \
				state/state_21_25.c \
				state/state_26_29.c \
				tokenize.c \
				expand.c \

PARSING		:=	$(PARSING:%=$(PARSING_DIR)/%)
PARSING_OBJ	=	$(PARSING:$(PARSING_DIR)/%.c=$(BUILD_DIR)/%.o)
PARSING_DEP	=	$(PARSING_OBJ:$(BUILD_DIR)/%.o=$(BUILD_DIR)/%.d)



CC			=	cc
CFLAGS		=	-Wall -Wextra -g3 -MMD -MP -I include
INCLUDE		=	-I include \
				-I libft/include \
				-I libft/ft_printf/include \
				-I libft/get_next_line/include

MAKEFLAGS	+=	--no-print-directory
DIR_DUP		=	mkdir -p $(@D)


all		:	$(NAME)

$(NAME)		:	$(MAIN_OBJ) $(BUILTIN_OBJ) $(EXEC_OBJ) $(PARSING_OBJ)
	@if [ ! -e "$(LIBFT)" ]; then \
		make -C libft; \
	fi
	$(CC) $(MAIN_OBJ) $(BUILTIN_OBJ) $(EXEC_OBJ) $(PARSING_OBJ) $(LIBFT) -lreadline -o $(NAME)


$(BUILD_DIR)/%.o		:	$(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


$(BUILD_DIR)/%.o		:	$(BUILTIN_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


$(BUILD_DIR)/%.o		:	$(EXEC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


$(BUILD_DIR)/%.o		:	$(PARSING_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


-include $(MAIN_DEP) $(BUILTIN_DEP) $(EXEC_DEP) $(PARSING_DEP)

clean	:
	if [ -d "$(BUILD_DIR)" ]; then \
		rm -f $(MAIN_OBJ); \
		rm -f $(MAIN_DEP); \
		rm -f $(BUILTIN_OBJ); \
		rm -f $(BUILTIN_DEP); \
		rm -f $(EXEC_OBJ); \
		rm -f $(EXEC_DEP); \
		rm -f $(PARSING_OBJ); \
		rm -f $(PARSING_DEP); \
		rm -rf $(BUILD_DIR); \
		make clean -C libft; \
	fi

fclean	:	clean
	if [ -e "$(NAME)" ]; then \
		rm -f $(NAME); \
	fi
	if [ -e "$(LIBFT)" ]; then \
		make fclean -C libft; \
	fi

re		:	fclean all

.PHONY	:	clean fclean re
.SILENT	:	clean fclean
