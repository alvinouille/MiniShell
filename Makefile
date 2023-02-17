# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 17:30:47 by mmeguedm          #+#    #+#              #
#    Updated: 2023/02/17 17:42:22 by mmeguedm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --------- Prerequisites ------------------------------------------------------

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I $(INC_PATH)

LIBS		= -L/usr/local/lib -I/usr/local/include -lreadline


# --------- Include files path ------------------------------------------------------

INC_PATH	= /mnt/nfs/homes/mmeguedm/Desktop/Projects/MiniShell/inc

# --------- Sources files path ------------------------------------------------------

SRC_PATH	= srcs/
PS_SRC_PATH	= $(SRC_PATH)parsing/
MN_SRC_PATH	= $(SRC_PATH)main/

# --------- Objects files path ------------------------------------------------------

OBJ_PATH	= obj/
PS_OBJ_PATH = $(OBJ_PATH)parsing/
MN_OBJ_PATH = $(OBJ_PATH)main/


PARS_SRCS	= inutils.c 		\
			lst.c 			\
			split_utils.c 	\
			split.c			\
			tokenisation.c	\
			trash.c			\
			utils.c			\
			split_state.c

MAIN_SRCS = main.c

#	OBJECTS FILES
OBJ = $(SRCS:.c=.o)
PARS_OBJ = $(PARS_SRCS:.c=.o)
MAIN_OBJ = $(MAIN_SRCS:.c=.o)

#	
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))
PARS_OBJS = $(addprefix $(PS_OBJ_PATH), $(PARS_OBJ))
MAIN_OBJS = $(addprefix $(MN_OBJ_PATH), $(MAIN_OBJ))

DEP = $(OBJS:.o=.d)

$(PS_OBJ_PATH)%.o : $(PS_SRC_PATH)%.c
	@mkdir -p $(PS_OBJ_PATH)
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH)

$(MN_OBJ_PATH)%.o : $(MN_SRC_PATH)%.c
	@mkdir -p $(MN_OBJ_PATH)
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH)

test : CFLAGS+= -g3 -fsanitize=address -MMD

all : $(NAME)

$(NAME) : $(PARS_OBJS) $(MAIN_OBJS)
	@$(CC) $(CFLAGS) $(PARS_OBJS) $(MAIN_OBJS) $(LIBS) -o $(NAME) -I $(INC_PATH)
	@printf "\n"
	@echo "Compiling done"

test : fclean $(NAME)

clean :
		rm -rf $(OBJ_PATH) 

fclean : clean
		rm -rf $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re directories

-include $(DEP)
