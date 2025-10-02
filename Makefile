NAME = libasm
LIB = libasm.a

# src files
MAIN_SRC = src/main.c
ASM_SRC = src/ft_strlen.s

# object files
OBJDIR = obj
ASM_OBJ = $(ASM_SRC:src/%.s=$(OBJDIR)/%.o)
MAIN_OBJ = $(MAIN_SRC:src/%.c=$(OBJDIR)/%.o)

CC = gcc
AS = nasm
CFLAGS = -Wall -Wextra -Werror
INC = -Iinclude
ASMFLAGS = -f elf64
RM = rm -f
RMDIR = rm -rf

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(LIB): $(ASM_OBJ)
	ar rcs $(LIB) $(ASM_OBJ)

$(NAME): $(LIB) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(MAIN_OBJ) -L. -lasm

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR)/%.o: src/%.s
	$(AS) $(ASMFLAGS) $< -o $@

clean:
	$(RM) $(ASM_OBJ) $(MAIN_OBJ)

fclean:
	$(RM) $(NAME) $(LIB)
	$(RMDIR) $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
