NAME = libftprintf.a

SRCS_PATH = srcs
SRC_FILES = ft_printf.c parser.c converter.c uconverter.c padding.c \
			convert_unicode.c set_conv.c get_flags.c
SRCS = $(addprefix $(SRCS_PATH)/,$(SRC_FILES))

OBJS_PATH = objects
OBJS_NAME = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJS_PATH)/,$(OBJS_NAME))

INCLUDES_PATH = includes
INCLUDES_NAME = ft_printf.h
INCLUDES = $(addprefix $(INCLUDES_PATH)/,$(INCLUDE_NAME))

CFLAGS = -Wall -Wextra -Werror

LIBFT_PATH = libft
LIB = $(addprefix $(LIBFT_PATH)/,libft.a)

.SILENT: all, clean, fclean, re
.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): libftcomp $(OBJS) $(LIB)
	@echo "\033[31;5;mCompiling ft_printf...\033[0m"
	ar rc $(NAME) $(LIB) $(OBJS)
	ranlib $(NAME)
	@echo "\033[32;3m\nCompiling Done !\033[0m"

libftcomp:
	@echo "\033[31;5;mCompiling libft...\033[0m"
	@make all -C libft/

$(OBJS): $(OBJS_PATH) $(SRCS) $(INCLUDES_PATH)
	@echo "compiling source"
	gcc -c $(SRCS) $(CFLAGS) -I$(INCLUDES_PATH)
	@mv $(OBJS_NAME) $(OBJS_PATH)

$(OBJS_PATH):
	@mkdir $(OBJS_PATH) 2> /dev/null || true

$(INCLUDES_PATH):
	@mkdir $(INCLUDES_PATH) 2> /dev/null || true
	@mv $(INCLUDE_NAME) $(INCLUDES_PATH)

clean:
	@echo "\033[32;5mCleaning..."
	@make clean -C libft/
	@rm -f $(OBJS)
	@rmdir $(OBJS_PATH) 2> /dev/null || true
	@echo "\033[32;3mCleaning Done !\n\033[0m"

fclean: clean
	@echo "\033[32;5mFcleaning..."
	@make fclean -C libft/
	@rm -f $(NAME)
	@echo "\033[32;3mFcleaning Done !\n\033[0m"

re: fclean all
