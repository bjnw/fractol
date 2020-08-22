NAME := fractol
BUILD_DIR := build
SRC := main.c init.c event.c action.c menu.c draw.c cmap.c viewport.c \
	buffalo.c burning_ship.c cosine_mandelbrot.c julia.c \
	mandelbrot.c perpendicular_celtic.c perpendicular_mandelbrot.c
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(OBJ:%.o=%.d)

LFT_DIR := libft
LFT_LIB := -L$(LFT_DIR) -lft

ifeq ($(shell uname -s), Linux)
	MLX_DIR := minilibx_linux
	MLX_LIB := -lXext -lX11
else
	MLX_DIR := minilibx_macos
	MLX_LIB := -framework OpenGL -framework AppKit
endif
MLX_LIB += -L$(MLX_DIR) -lmlx

CC := clang
# AR := llvm-ar
# RANLIB := llvm-ranlib
AR := ar
RANLIB := ranlib

CC := clang
WFLAGS := -Wall -Wextra
# WFLAGS += -Werror
# WFLAGS += -Wpedantic
# OFLAGS := -g
OFLAGS := -O2 -march=native
OFLAGS += -ftree-vectorize
OFLAGS += -ffast-math
# OFLAGS += -flto=thin
# OFLAGS += -fPIC
CFLAGS := $(WFLAGS) $(OFLAGS) -MMD -I$(LFT_DIR)/include -I$(MLX_DIR) -Iinclude
LFLAGS := $(LFT_LIB) $(MLX_LIB) -pthread -lm

vpath %.c src src/iter

.PHONY: all clean fclean re test love debug

$(NAME): $(OBJ)
	@$(MAKE) -sC $(MLX_DIR) all
	@$(MAKE) -sC $(LFT_DIR) all
	@printf "[$(NAME)] Linking objects...\n"
	@$(CC) $(OBJ) -o $(NAME) $(LFLAGS)
	@printf "\033[32;1m[$(NAME)] Done\033[0m\n"

-include $(DEP)
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@printf "[$(NAME)] Building object '$@'\n"
	@$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME)

clean:
	@$(MAKE) -sC $(MLX_DIR) clean
	@$(MAKE) -sC $(LFT_DIR) clean
	@rm -rf $(BUILD_DIR)

fclean: clean
	# @$(MAKE) -sC $(MLX_DIR) fclean
	@$(MAKE) -sC $(LFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

test: all
	@./$(NAME) 0

love:
	@printf 'not war\n'
