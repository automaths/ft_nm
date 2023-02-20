NAME        :=	ft_nm

SRC_DIR     := 	src
OBJ_DIR     := 	obj
SRCS        := 	main.c \
				parsing_argv.c \
				libft/ft_strlen.c \
				libft/ft_memcpy.c \
				libft/ft_strncmp.c \
				libft/ft_substr.c \
				libft/ft_split.c \
				libft/ft_strdup.c \
				libft/ft_isalnum.c \
				libft/ft_isalpha.c \
				utils/garbage.c \
				displaying.c \
				typing.c \
				utils/element.c \
				parsing_elf.c \
				sorting.c \


SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I include

RM          := rm -f
MAKEFLAGS   += --no-print-directory
DIR_DUP     = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) -o $(NAME)
		$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		$(DIR_DUP)
		$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
		$(info CREATED $@)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re:
		$(MAKE) fclean
		$(MAKE) all

.PHONY: clean fclean re
.SILENT:

