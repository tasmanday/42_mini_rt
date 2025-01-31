#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tday <tday@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/19 19:36:12 by tday              #+#    #+#              #
#    Updated: 2025/02/01 00:15:09 by tday             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Variables
NAME            :=      miniRT
SRC_DIRS        :=      src/main src/parsing src/ray_casting src/vectors       \
                        src/mlx
OBJ_DIR         :=      obj
INC_DIR         :=      inc
LIBFT_DIR       :=      libft
LIBFT           :=      $(LIBFT_DIR)/libft.a

# Detect Operating System
OS := $(shell uname)

ifeq ($(OS), Darwin)
    MLX_DIR     :=      ./minilibx_macos/
    MLX_FLAGS   :=      -framework OpenGL -framework AppKit
else
    MLX_DIR     :=      ./minilibx_linux/
    MLX_FLAGS   :=      -lXext -lX11 -lm
endif

CC              :=      gcc
CFLAGS          :=      -Wall -Wextra -Werror -O3

# Define source and object files
SRCS			:=		$(addprefix src/main/, main.c)							\
						$(addprefix src/initialisation/, init.c)				\
						$(addprefix src/mlx/, mlx.c)							\
						$(addprefix src/free/, free_everything.c)				\
						$(addprefix src/parsing/, error.c file_check.c 			\
									object_utils.c error_utils.c				\
									parse_elements.c parse_main.c 				\
									parse_objects.c parse_utils.c utils.c		\
									print_elements.c print_objects.c			\
									print_utils.c)								\
						$(addprefix src/ray_casting/, compute_ray_directions.c	\
									sphere_intersection.c 						\
									cylinder_intersection.c						\
									plane_intersection.c trace_rays.c			\
									intersection.c lighting_and_shadows.c		\
									anti-aliasing.c)							\
						$(addprefix src/vectors/, vector_operations.c)				

OBJS            :=      $(SRCS:src/%.c=$(OBJ_DIR)/%.o)
RM              :=      rm -f

.SILENT:

# Create object directories
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@$(call check_dir_change,$<)

# Function definition
define check_dir_change
$(eval CUR_DIR := $(patsubst src/%/,%, $(dir $(1))))
$(if $(filter-out $(LAST_DIR),$(CUR_DIR)), @echo "$(YELLOW)$(CUR_DIR) functions compiled successfully!$(DEFAULT_COLOUR)")
$(eval LAST_DIR := $(CUR_DIR))
endef

# Colours
DEFAULT_COLOUR  :=      \033[0m
GREEN           :=      \033[1;32m
MAGENTA         :=      \033[1;35m
YELLOW          :=      \033[1;33m
CYAN            :=      \033[1;36m
BLUE            :=      \033[1;34m
RED             :=      \033[1;31m

# Targets
all: build_minilibx $(LIBFT) $(NAME)

$(LIBFT):        
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS)
#	@$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) -I$(MLX_DIR) -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME)
	@echo "$(GREEN)--> SUCCESS! Everything compiled and linked into executable: $(BLUE)$(NAME)$(DEFAULT_COLOUR)"
	@echo "\n"

build_minilibx:
	@echo "Building MiniLibX..."
	@cd $(MLX_DIR) && $(MAKE)

fclean_minilibx:
	@echo "\n"
	@echo "$(RED)Fully cleaning MiniLibX...$(DEFAULT_COLOUR)"
	@cd $(MLX_DIR) && $(MAKE) clean
	@cd $(MLX_DIR) && rm -f *.o libmlx.a libmlx_Linux.a

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)
	@echo "$(RED)--> SUCCESS! Object files deleted$(DEFAULT_COLOUR)"

fclean: fclean_minilibx clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(RM) $(OBJS) $(NAME)
	@echo "$(RED)--> SUCCESS! $(RST)$(BLUE)$(NAME)$(RED) deleted$(DEFAULT_COLOUR)"
	@echo "\n"

re: fclean all

.PHONY: all clean fclean re build_minilibx fclean_minilibx