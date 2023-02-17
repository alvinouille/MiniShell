# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 17:30:47 by mmeguedm          #+#    #+#              #
#    Updated: 2023/02/17 20:53:43 by mmeguedm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --------- Prerequisites ------------------------------------------------------

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I $(INC_PATH)

LIBS		= -L/usr/local/lib -I/usr/local/include -lreadline

RED='\033[0;32m'
# --------- Include files path ------------------------------------------------------

INC_PATH	= /mnt/nfs/homes/mmeguedm/Desktop/Projects/MiniShell/inc/

# --------- Sources files path ------------------------------------------------------

SRC_PATH	= srcs/
PS_SRC_PATH	= $(SRC_PATH)parsing/
MN_SRC_PATH	= $(SRC_PATH)main/

# --------- Objects files path ------------------------------------------------------

OBJ_PATH	= obj/
PS_OBJ_PATH = $(OBJ_PATH)parsing/
MN_OBJ_PATH = $(OBJ_PATH)main/

# --------- Header files -----------------------------------------------------------

INC			= $(addprefix $(INC_PATH),		\
					minishell.h				\
					tools.h					\
					utils.h					\
					lst.h					\
				)

# --------- Sources files -----------------------------------------------------------

SRC			=	$(addprefix $(SRC_PATH),					\
					main/main.c								\
					$(addprefix parsing/,					\
						inutils.c 							\
						lst.c 								\
						split_utils.c 						\
						split.c								\
						tokenisation.c						\
						trash.c								\
						utils.c								\
						split_state.c						\
					)										\
				)

# --------- Object files ------------------------------------------------------------

OBJ			=	$(patsubst srcs/%.c, obj/%.o, $(SRC))

# --------- Compiling ---------------------------------------------------------------

obj/%.o: srcs/%.c $(INC)
	@ mkdir -p $(dir $@)
	@ printf "%-60s\r" "'\033[0;31m'Compiling $<"
	@ $(CC) $(CFLAGS) -c $< -o $@

# --------- Linking -----------------------------------------------------------------

$(NAME) : $(OBJ) $(INC)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $(NAME)
	@printf "\n"
	@echo "Compiling done !"
	@cat .femtoshell.logo

# --------- Phony targets -----------------------------------------------------------

all : $(NAME)

test : fclean $(NAME)

test : CFLAGS+= -g3 -fsanitize=address -MMD

clean :
		rm -rf $(OBJ_PATH) 

fclean : clean
		rm -rf $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re directories test
