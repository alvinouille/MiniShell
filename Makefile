# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 17:30:47 by mmeguedm          #+#    #+#              #
#    Updated: 2023/04/24 20:19:41 by mmeguedm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --------- Prerequisites ------------------------------------------------------

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I $(INC_PATH)

LIBS		= -L/usr/local/lib -I/usr/local/include -lreadline

# --------- Include files path ------------------------------------------------------

INC_PATH	= inc/

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
					builtins.h				\
					clean.h					\
					exec.h					\
					expansion.h				\
					here_doc.h				\
					env.h					\
					parsing.h				\
				)

# --------- Sources files -----------------------------------------------------------

SRC			=	$(addprefix $(SRC_PATH),					\
					main/main.c								\
					$(addprefix parsing/,					\
						cmd_creator.c						\
						cmd_utils.c 						\
						env_utils.c 						\
						env_functions.c 					\
						env.c								\
						first_split.c						\
						lst_utils.c							\
						parse_error.c						\
						first_split_utils.c					\
						first_split_utils2.c 				\
						token_creator.c						\
						tokenisation.c						\
						trash.c								\
						ft_itoa.c							\
						utils.c								\
						utils2.c 							\
						utils3.c 							\
						split_state.c						\
						split_utils.c 						\
						error.c								\
						tokjoin.c							\
						lst.c								\
						lst_print.c							\
						expansion.c							\
						exp_state.c 						\
						exp_utils.c 						\
						split.c								\
						extra.c								\
					)										\
					$(addprefix exec/,						\
						here_doc.c							\
						opening.c							\
						signal.c							\
					)										\
					$(addprefix pipex/,						\
						error.c								\
						get_path.c							\
						pipex.c								\
						utils_pipex_01.c					\
						clean_close.c					\
						exec.c								\
						exec_built.c 						\
					)										\
					$(addprefix builtins/,					\
						cd.c 								\
						echo.c 								\
						env.c 								\
						exit.c 								\
						export.c 							\
						pwd.c 								\
						unset.c 							\
					)										\
				)

# --------- Object files ------------------------------------------------------------

OBJ			=	$(patsubst srcs/%.c, obj/%.o, $(SRC))

# --------- Compiling ---------------------------------------------------------------

obj/%.o: srcs/%.c $(INC)
	@ mkdir -p $(dir $@)
	@ printf "%-60s\r" "Compiling $<"
	@ $(CC) $(CFLAGS) -c $< -o $@

# --------- Linking -----------------------------------------------------------------

$(NAME) : $(OBJ) $(INC) Makefile
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)
	@printf "\n\n"
	@echo "\033[1;32mCompiling done !"
	@echo "\033[1;36m"
	@cat .femtoshell.logo.c
	@echo "\033[0m"

# --------- Phony targets -----------------------------------------------------------

all : $(NAME)

clean :
		rm -rf $(OBJ_PATH)

fclean : clean
		rm -rf $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re directories test
