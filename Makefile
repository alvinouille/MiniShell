NAME = pipex

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRC_PATH = src/
INC_PATH = inc/
OBJ_PATH = obj/

SRCS =  error.c				\
		get.c				\
		here_doc.c			\
		main.c				\
		get_next_line.c		\
		list.c				\
		extra.c				\
		split.c				\
		utils.c				\
		utils2.c

OBJ = ${SRCS:.c=.o}

OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@echo [CC] $<
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_PATH)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\n"
	@echo "Compiling done"

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re
