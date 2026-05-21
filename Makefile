NAME		= libasm
LIB			= libasm.a

MAIN_SRC	= src/main.c
ASM_SRC		= src/ft_strlen.s \
			  src/ft_strcpy.s \
			  src/ft_strcmp.s \
			  src/ft_write.s \
			  src/ft_read.s \
			  src/ft_strdup.s

OBJDIR		= obj
ASM_OBJ		= $(ASM_SRC:src/%.s=$(OBJDIR)/%.o)
MAIN_OBJ	= $(MAIN_SRC:src/%.c=$(OBJDIR)/%.o)

CC			= gcc
AS			= nasm
CFLAGS		= -Wall -Wextra -Werror
INC			= -Iinclude
ASFLAGS		= -f elf64
RM			= rm -f

all: $(NAME)

$(LIB): $(ASM_OBJ)
	ar rcs $@ $^

$(NAME): $(LIB) $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJ) -L. -lasm

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJDIR)/%.o: src/%.s | $(OBJDIR)
	$(AS) $(ASFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	$(RM) $(ASM_OBJ) $(MAIN_OBJ)

fclean: clean
	$(RM) $(NAME) $(LIB)
	$(RM) -r $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
