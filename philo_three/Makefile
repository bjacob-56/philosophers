SRC_DIR	:= srcs/
OBJ_DIR	:= obj/

OBJ_DIRS = $(addprefix $(OBJ_DIR), main clear utils)

PRE_SRCS =	main/philo_three main/init_philo_three main/activity main/philo_utils main/childs \
			utils/lst_utils utils/nb_utils utils/str_utils \
			clear/errors clear/clear_objects

SRCS = $(addsuffix .c, $(addprefix $(SRC_DIR), $(PRE_SRCS)))
OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(PRE_SRCS)))

NAME = philo_three

CC = clang
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
THFLAGS = -lpthread -D_REENTRANT
INC =	-I./includes 

all:	$(NAME)

$(NAME): $(OBJ_DIRS) $(OBJS)
	$(CC) $(CFLAGS) $(THFLAGS) $(OBJS) $(INC) -o $(NAME) 
	@echo "----- \033[32m $@ created\033[0m  -----"

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(OBJS) : includes/philosophers.h

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$@ \033[32mcreated\033[0m"

clean:
	rm -rf $(OBJ_DIR)

fclean: 	clean
	rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re
