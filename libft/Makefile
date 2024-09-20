# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rgallien <rgallien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 16:19:48 by lvicino           #+#    #+#              #
#    Updated: 2024/09/20 12:17:29 by rgallien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

OBJ_DIR		=	obj


SRC_DIR		=	src

SRC			=	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c

SRC			:=	$(SRC:%=$(SRC_DIR)/%)
OBJ			=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)



DIR_PRINTF	= ft_printf/src

SRC_PRINTF	=	ft_printf.c \
				ft_put_hex.c \
				ft_put_unbr.c \
				ft_put_utils.c

SRC_PRINTF	:=	$(SRC_PRINTF:%=$(DIR_PRINTF)/%)
OBJ_PRINTF	=	$(SRC_PRINTF:$(DIR_PRINTF)/%.c=$(OBJ_DIR)/%.o)



DIR_GNL	= get_next_line/src

SRC_GNL	=	get_next_line.c

SRC_GNL	:=	$(SRC_GNL:%=$(DIR_GNL)/%)
OBJ_GNL	=	$(SRC_GNL:$(DIR_GNL)/%.c=$(OBJ_DIR)/%.o)



BSRC_DIR	=	src_bonus

BSRC 		=	ft_lstnew_bonus.c \
				ft_lstadd_front_bonus.c \
				ft_lstsize_bonus.c \
				ft_lstlast_bonus.c \
				ft_lstadd_back_bonus.c \
				ft_lstdelone_bonus.c \
				ft_lstclear_bonus.c \
				ft_lstiter_bonus.c \
				ft_lstmap_bonus.c

BSRC		:=	$(BSRC:%=$(BSRC_DIR)/%)
BOBJ		=	$(BSRC:$(BSRC_DIR)/%.c=$(OBJ_DIR)/%.o)



CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
INCLUDE		=	-I include -I ft_printf/include -I get_next_line/include

MAKEFLAGS	+=	--no-print-directory
DIR_DUP		=	mkdir -p $(@D)


all		:	$(NAME)

$(NAME)	:	$(OBJ) $(BOBJ) $(OBJ_PRINTF) $(OBJ_GNL)
	ar rcs $(NAME) $(OBJ) $(BOBJ) $(OBJ_PRINTF) $(OBJ_GNL)


$(OBJ_DIR)/%.o		:	$(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


$(OBJ_DIR)/%.o		:	$(DIR_PRINTF)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


$(OBJ_DIR)/%.o		:	$(DIR_GNL)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


$(OBJ_DIR)/%.o		:	$(BSRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<


clean	:
	if [ -d "$(OBJ_DIR)" ]; then \
		rm -f $(OBJ); \
		rm -f $(OBJ_PRINTF); \
		rm -f $(OBJ_GNL); \
		rm -f $(BOBJ); \
		rmdir $(OBJ_DIR); \
	fi

fclean	:	clean
	rm -f $(NAME)

re		:	fclean all

.PHONY	:	clean fclean re
.SILENT	:	clean fclean
