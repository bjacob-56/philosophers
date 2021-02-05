SRC_DIR	:= srcs/
OBJ_DIR	:= obj/

OBJ_DIRS = $(addprefix $(OBJ_DIR), philo_one philo_two philo_three clear utils)

PRE_SRCS_ONE =	philo_one/philo_one philo_one/init_philo_one philo_one/activity philo_one/philo_utils \
				utils/lst_utils utils/nb_utils \
				clear/errors clear/clear_objects


SRCS_ONE = $(addsuffix .c, $(addprefix $(SRC_DIR), $(PRE_SRCS_ONE)))
OBJS_ONE = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(PRE_SRCS_ONE)))

NAME_ONE = philo_one
NAME_TWO = philo_two
NAME_THREE = philo_three

CC = clang
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
THFLAGS = -lpthread -D_REENTRANT
# CFLAGS = -Wall -Wextra -Werror -g3
INC =	-I./includes 

all:	$(NAME_ONE) $(NAME_TWO) $(NAME_THREE)

$(NAME_ONE): $(OBJ_DIRS) $(OBJS_ONE)
	$(CC) $(CFLAGS) $(THFLAGS) $(OBJS_ONE) $(INC) -o $(NAME_ONE) 
	@echo "----- \033[32m $@ created\033[0m  -----"

$(NAME_TWO):

$(NAME_THREE):

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(OBJS_ONE) : includes/philosophers.h

$(OBJS_TWO) : includes/philosophers.h

$(OBJS_THREE) : includes/philosophers.h

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$@ \033[32mcreated\033[0m"

clean:
	rm -rf $(OBJ_DIR)

fclean: 	clean
	rm -f $(NAME_ONE) $(NAME_TWO) $(NAME_THREE)

re:		fclean all

.PHONY: all clean fclean re
