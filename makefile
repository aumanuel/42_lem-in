# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amanuel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/24 01:22:10 by tmanuel           #+#    #+#              #
#    Updated: 2019/03/12 00:51:54 by amanuel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Binary

NAME =	lem-in 



# Path

SRC_PATH = ./srcs/

OBJ_PATH = ./objs/

INC_PATH = ./includes/



# Name

SRC_NAME = lemin_part1.c \
		   lemin_part2.c \

OBJ_NAME = $(SRC_NAME:.c=.o)



# Files

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))



# Flags

FLAGS = -Wall -Wextra -Werror 



# Libft

LIB =  -L libft/ -lft



# Display

ifndef ECHO
	T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
		-nrRf $(firstword $(MAKEFILE_LIST)) \
		ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
	N := x
	C = $(words $N)$(eval N := x $N)
	ECHO = printf "\r[`expr $C '*' 100 / $T`%%]"
endif



# Rules

all: $(NAME) 

$(NAME): $(OBJ) 
	@make -C libft/
	@gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIB)
	@printf "\rLem-in done                \n"
	@tput cvvis

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@tput civis
	@gcc $(FLAGS) -I$(INC_PATH) -o $@ -c $<
	@tput setaf 10
	@$(ECHO)
	@echo -n $@
	@printf "                              "

clean:
	@rm -rf $(OBJ_PATH)
	@make -C libft/ clean
	@tput setaf 9
	@echo "Lem-in clean"

fclean: 
	@rm -f $(NAME)
	@rm -rf $(OBJ_PATH)
	@make -C libft/ fclean
	@tput setaf 9
	@echo "Lem-in fclean"

re:
	@make fclean && make

.PHONY: all clean fclean re
