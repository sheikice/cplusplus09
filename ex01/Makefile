# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwuille <jwuille@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/17 14:16:44 by jwuille           #+#    #+#              #
#    Updated: 2026/01/21 15:09:46 by jwuille          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ_DIR = obj

SRC =	\
		RPN.cpp \
		main.cpp

CC = c++ -MD -std=c++98
CFLAGS = -Wall -Werror -Wextra -g3
NAME = RPN

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# ================== SRC =============================
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean_obj:
	@rm -rf $(OBJ_DIR)

clean:
	rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	@rm -f compile_commands.json
 
re: fclean all

-include $(OBJ_DIR)/*.d

.PHONY: all clean fclean re bonus 
