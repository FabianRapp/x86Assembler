NAME := assembler
CC := cc
CFLAGS_DEBUG := -Wall -Wextra -DFSAN -fsanitize=address -g -O0
CFLAGS := $(CFLAGS_DEBUG)
#-Werror
#-O3
LIBFT_DIR = libft/
LIBFT 	=	$(LIBFT_DIR)libft.a
INCLUDES=	-I./include \
			-I./include/instruction_set \
			-I./include/instruction_set/operands \
			-I./include/elf \
			-I./libft \

ifeq ($(OS), Darwin)
	#mac
else
endif

SRC_DIR := src/
SRC_MAIN := main.c
SRC_TEST_MAIN := main.c

SRC_INIT := \
	init/init.c \

SRC_INSTRUCTION_SET := \
	instruction_set/instruction_set.c \
	instruction_set/mov.c \
	instruction_set/operands/init.c \
	instruction_set/operands/cleanup.c \
	instruction_set/operands/gp_reg_operand.c \
	instruction_set/operands/empty_operand.c \
	lexer/lexer.c \
	ir.c \
	elf/elf_header.c \

SOURCE_FILES := \
	$(SRC_MAIN) \
	$(SRC_INIT) \
	$(SRC_INSTRUCTION_SET) \

SOURCES = $(SOURCE_FILES:%=$(SRC_DIR)%)

OBJ_DIR := o_files/
OBJECTS = $(SOURCE_FILES:%.c=$(OBJ_DIR)%.o)

ASM_DIR := asm/
ASM_FILES = $(SOURCE_FILES:%.c=$(ASM_DIR)%.s)

TEST_INPUT := input.asm

NAME_TEST := tests.out



GREEN	=	\033[0;32m
YELLOW	=	\033[33m
CYAN	=	\033[0;36m
CLEAR	=	\033[0m

.PHONY: all clean fclean ffclean test redebug print_vars compile_raw_test cmp

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBFT) -o $(NAME) $(CFLAGS)
	@echo "$(GREEN)$(NAME) compiled!$(CLEAR)"

asm: $(ASM_FILES)
	@echo "$(GREEN)Compiled as files!$(CLEAR)"

cmp:
	make raw_test && cat input.asm && xxd -b test.bin && ./assembler >tmp_out && xxd -b out.bin

print_vars:
	#@echo "$(YELLOW)REFLECTIONS: $(CLEAR)$(GREEN)$(REFLECTIONS) $(CLEAR)$(YELLOW)(any integer >= 0) $(CLEAR)"
	#@echo "$(YELLOW)SHADOWS: $(CLEAR)$(GREEN)'$(SHADOWS)' $(CLEAR)$(YELLOW)('SMOOTH\' or 'HARD') $(CLEAR)"
	#@echo "$(YELLOW)AMBIENT: $(CLEAR)$(GREEN)'$(AMBIENT)' $(CLEAR)$(YELLOW)('42' or 'CUSTOM') $(CLEAR)"
	#@echo "$(YELLOW)CAMERA: $(CLEAR)$(GREEN)'$(CAMERA)' $(CLEAR)$(YELLOW)('42' or 'GOOD') $(CLEAR)"

debug:
	make CFLAGS="$(CFLAGS_DEBUG)"

redebug: fclean debug

raw_test: $(TEST_INPUT)
	@as -o test.o $(TEST_INPUT)
	@ld -o test.bin --oformat binary test.o
	@rm test.o

test: clean libft
	make $(NAME_TEST) SRC_MAIN="$(SRC_TEST_MAIN)" NAME=$(NAME_TEST)


clean:
	@rm -f $(ASM_FILES)
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

$(ASM_DIR)%.s: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@gcc $(INCLUDES) -S -m64 $< -o $@

$(LIBFT): $(LIBFT_DIR)
	@cd libft && make CFLAGS="$(CFLAGS)"

$(LIBFT_DIR):
	@if [ "$(USER)" = "frapp" ] || [ "$(USER)" = "fabi" ] ; then \
		echo "$(GREEN) User $(USER) recognized, cloning via SSH$(CLEAR)"; \
		git clone git@github.com:FabianRapp/libft.git $(LIBFT_DIR);\
	else \
		git clone https://github.com/FabianRapp/libft.git $(LIBFT_DIR);\
	fi

PWD = $(shell pwd)

compile_commands:
	@echo '[' > compile_commands.json
	@$(foreach src, $(SOURCES), \
		echo "\t{" >> compile_commands.json; \
		echo "\t\t\"directory\": \"$(PWD)\"," >> compile_commands.json; \
		echo "\t\t\"command\": \"$(CC) $(CFLAGS) $(INCLUDES) -o $(OBJS_DIR)$$(basename $(src) .c).o $(src)\"," >> compile_commands.json; \
		echo "\t\t\"file\": \"$(src)\"" >> compile_commands.json; \
		echo "\t}," >> compile_commands.json;)
	@sed -i '' -e '$$ d' compile_commands.json
	@echo "\t}" >> compile_commands.json
	@echo ']' >> compile_commands.json
	@echo "$(YELLOW) Pseudo compile_commands.json generated $(CLEAR)"

