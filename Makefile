# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tday <tday@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 19:36:12 by tday              #+#    #+#              #
#    Updated: 2024/08/25 00:04:01 by tday             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

NAME 			:=		mini_rt
SRC_DIRS 		:=		src/main src/initialisation src/frame src/controls		\
						src/window src/ray_casting
INC_DIR 		:=		inc
MLX_DIR			:=		minilibx_linux
LIBFT_DIR		:=		libft
LIBFT			:=		$(LIBFT_DIR)/libft.a
CC				:=		gcc
CFLAGS			:=		-Wall -Wextra -Werror -O3
MLX_FLAGS		:=		-L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
SRCS			:=		$(addprefix src/main/, main.c)							\
						$(addprefix src/mlx/, mlx.c)							\
						$(addprefix src/parsing/, error.c file_check.c 			\
									parse_elements.c parse_main.c 				\
									parse_objects.c parse_utils.c utils.c		\
									print_elements.c print_objects.c)			\
						$(addprefix src/vectors/, vector_operations.c)			\
						$(addprefix src/ray_casting/, compute_ray_directions.c	\
									sphere_intersection.c)
OBJS			:=		$(SRCS:.c=.o)
RM				:=		rm -f

# Function definition
define check_dir_change
$(eval CUR_DIR := $(patsubst src/%/,%, $(dir $(1))))
$(if $(filter-out $(LAST_DIR),$(CUR_DIR)), @echo 								\
"$(GREEN)$(CUR_DIR) functions compiled successfully!$(DEFAULT_COLOUR)")
$(eval LAST_DIR := $(CUR_DIR))
endef

# Colours

DEFAULT_COLOUR	:=		\033[0m
GRAY			:=		\033[1;30m
RED				:=		\033[1;31m
GREEN			:=		\033[1;32m
YELLOW			:=		\033[1;33m
BLUE			:=		\033[1;34m
MAGENTA			:=		\033[1;35m
CYAN			:=		\033[1;36m
WHITE			:=		\033[1;37m

# Targets

all: $(NAME)

$(NAME): 		$(LIBFT) $(OBJS)
#				@$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -L$(LIBFT_DIR) -lft -lm -o $(NAME)
				@$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -L$(LIBFT_DIR) -lft -I$(MLX_DIR) $(MLX_FLAGS)	-o $(NAME)
				@echo "$(CYAN)Everything compiled and linked into executable: $(BLUE)$(NAME)$(DEFAULT_COLOUR)"
				@echo "\n"

$(LIBFT):		
				@$(MAKE) -s -C $(LIBFT_DIR)

$(OBJS):		%.o: %.c
#				@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
				@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_DIR) -c $< -o $@
				@$(call check_dir_change,$<)

clean:			
				@$(RM) $(OBJS)
				@$(foreach dir,$(SRC_DIRS),echo "$(MAGENTA)$(notdir 			\
				$(patsubst %/,%,$(dir))) object files deleted.					\
				$(DEFAULT_COLOUR)";)

fclean: 		
				@$(MAKE) fclean -s -C $(LIBFT_DIR)
				@$(MAKE) -s clean
				@$(RM) $(NAME)
				@echo "$(YELLOW)$(NAME) deleted.$(DEFAULT_COLOUR)"
				@echo "\n"

re: 			fclean all

.PHONY: 		all clean fclean re
