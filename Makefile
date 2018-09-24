# NAME := editor

# LIB_DIR := ./libft/
# SRC_DIR := ./src/
# OBJ_DIR := ./obj/
# INC_DIR := ./inc/

# SRC := main.c editor.c points.c
# OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# CC := gcc
# FLAGS := -Wall -Wextra -Werror -O2
# # SDL_LIB := -L ~/.brew/lib/ -lSDL2 -lSDL2_image
# # LIBFT = $(LIB_DIR)libft.a 
# # LIBFT_FLAGS := -L $(LIB_DIR) -lft
# # LIBFT_INC := $(LIB_DIR)incs

# # HDR_FLAGS := -I $(LIBFT_INC) -I $(INC_DIR) -I ~/.brew/include/SDL2/

# SDL_LIB := -L /usr/local/Cellar/sdl2/2.0.8/lib -lSDL2 -lSDL2_image
# LIBFT = $(LIB_DIR)libft.a
# LIBFT_FLAGS := -L $(LIB_DIR) -lft
# LIBFT_INC := $(LIB_DIR)incs

# HDR_FLAGS := -I $(LIBFT_INC) -I $(INC_DIR) -I /usr/local/Cellar/sdl2/2.0.8/include

# all: $(NAME)

# $(NAME): $(LIBFT) $(OBJ)
# 	$(CC) $(OBJ) $(HDR_FLAGS) -o $(NAME) $(LIBFT) $(SDL_LIB) -D_THREAD_SAFE

# $(OBJ): | $(OBJ_DIR)

# $(OBJ_DIR):
# 	mkdir $(OBJ_DIR)

# $(OBJ_DIR)%.o: $(SRC_DIR)%.c
# 	$(CC) -c $< -o $@ $(FLAGS) $(HDR_FLAGS)

# $(LIBFT):
# 	make -C $(LIB_DIR)

# clean:
# 	make clean -C $(LIB_DIR)
# 	rm -f $(OBJ)

# fclean:
# 	make fclean -C $(LIB_DIR)
# 	rm -f $(NAME)
# 	rm -rf $(OBJ_DIR)

# re: fclean all

NAME := editor

LIB_DIR := ./libft/
SRC_DIR := ./src/
OBJ_DIR := ./obj/
INC_DIR := ./inc/

SRC := main.c editor.c points.c neighbors_diag.c draw.c check_end.c errors.c
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC := gcc
FLAGS := -Wall -Wextra -Werror -O2
SDL_LIB := -L ~/.brew/lib/ -lSDL2 -lSDL2_image
LIBFT = $(LIB_DIR)libft.a 
LIBFT_FLAGS := -L $(LIB_DIR) -lft
LIBFT_INC := $(LIB_DIR)incs

HDR_FLAGS := -I $(LIBFT_INC) -I $(INC_DIR) -I ~/.brew/include/SDL2/

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(HDR_FLAGS) -o $(NAME) $(LIBFT) $(SDL_LIB) -D_THREAD_SAFE -fsanitize=address

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< -o $@ $(FLAGS) $(HDR_FLAGS)

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	make clean -C $(LIB_DIR)
	rm -f $(OBJ)

fclean:
	make fclean -C $(LIB_DIR)
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all