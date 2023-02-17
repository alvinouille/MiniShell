NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -MMD

LIBS = -L/usr/local/lib -I/usr/local/include -lreadline

SRC_PATH = srcs/
INC_PATH = inc/
OBJ_PATH = obj/

SRCS =	main.c			\
		inutils.c		\
		lst.c			\
		split_utils.c	\
		split.c			\
		tokenisation.c	\
		trash.c			\
		utils.c			\
		split_state.c


OBJ = $(SRCS:.c=.o)


OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

DEP = $(OBJS:.o=.d)

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH)

test : CFLAGS= -Wall -Wextra -g3 -fsanitize=address -MMD


all : $(NAME)

$(NAME) :  $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
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
