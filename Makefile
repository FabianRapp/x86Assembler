NAME := assembler
CC := cc
CFLAGS_DEBUG := -Wall -Wextra -DFSAN -fsanitize=address -g -O0
CFLAGS := $(CFLAGS_DEBUG)
#-Werror
#-O3
LIBFT_DIR = libft/
LIBFT 	=	$(LIBFT_DIR)libft.a
INCLUDES= -I./include

ifeq ($(OS), Darwin)
	#mac
else
endif

SRC_DIR := src/
SRC_MAIN := main.c
SRC_TEST_MAIN := main.c

SOURCE_FILES := \
	$(SRC_MAIN) \

SOURCES = $(SOURCE_FILES:%=$(SRC_DIR)%)

OBJ_DIR := o_files/
OBJECTS = $(SOURCE_FILES:%.c=$(OBJ_DIR)%.o)

NAME_TEST := tests.out

GREEN	=	\033[0;32m
YELLOW	=	\033[33m
CYAN	=	\033[0;36m
CLEAR	=	\033[0m

.PHONY: all clean fclean ffclean test redebug print_vars

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT) -o $(NAME) $(CFLAGS)
	@echo "$(GREEN)$(NAME) compiled!$(CLEAR)"

print_vars:
	#@echo "$(YELLOW)REFLECTIONS: $(CLEAR)$(GREEN)$(REFLECTIONS) $(CLEAR)$(YELLOW)(any integer >= 0) $(CLEAR)"
	#@echo "$(YELLOW)SHADOWS: $(CLEAR)$(GREEN)'$(SHADOWS)' $(CLEAR)$(YELLOW)('SMOOTH\' or 'HARD') $(CLEAR)"
	#@echo "$(YELLOW)AMBIENT: $(CLEAR)$(GREEN)'$(AMBIENT)' $(CLEAR)$(YELLOW)('42' or 'CUSTOM') $(CLEAR)"
	#@echo "$(YELLOW)CAMERA: $(CLEAR)$(GREEN)'$(CAMERA)' $(CLEAR)$(YELLOW)('42' or 'GOOD') $(CLEAR)"

debug:
	make CFLAGS="$(CFLAGS_DEBUG)"

redebug: fclean debug

test: clean libft
	make $(NAME_TEST) SRC_MAIN="$(SRC_TEST_MAIN)" NAME=$(NAME_TEST)

clean:
	@rm -rf $(OBJ_DIR)
#@if [ -d $(OBJ_DIR) ]; then rmdir $(OBJ_DIR); fi
	@if [ -d $(LIBFT_DIR) ]; then cd libft && make clean; fi
	@echo "$(CYAN)object files cleaned$(CLEAR)"

fclean: clean
	@rm -f $(NAME) $(NAME_TEST)
	@if [ -d $(LIBFT_DIR) ]; then cd libft && make fclean; fi
	@echo "$(CYAN)miniRT fclean$(CLEAR)"

ffclean: fclean
	@rm -rf $(LIBFT_DIR)
	@echo "$(CYAN)miniRT ffclean$(CLEAR)"

re: fclean
	@make all

rre: ffclean
	@make all

prof: fclean
	@make CFLAGS="$(FLAGS_SPEED) -g -pg" CC=gcc

###utils
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT): $(LIBFT_DIR)
	@cd libft && make CFLAGS="$(CFLAGS)"

$(LIBFT_DIR):
	@if [ "$(USER)" = "frapp" ] || [ "$(USER)" = "fabi" ] ; then \
		echo "$(GREEN) User $(USER) recognized, cloning via SSH$(CLEAR)"; \
		git clone git@github.com:FabianRapp/libft.git $(LIBFT_DIR);\
	else \
		git clone https://github.com/FabianRapp/libft.git $(LIBFT_DIR);\
	fi
