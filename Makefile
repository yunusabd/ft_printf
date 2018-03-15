NAME = libftprintf.a

SRCS_PATH =  
SRCS = ft_printf.c parser.c converter.c uconverter.c padding.c

OBJS = $(SRCS:.c=.o)

INCLUDES_PATH = includes
INCLUDES_NAME = ft_printf.h
INCLUDES = $(addprefix $(INCLUDES_PATH)/,$(INCLUDE_NAME))

CFLAGS = -Wall -Werror -Wextra
LIB = libft/libft.a

.SILENT: all, clean, fclean, re
.PHONY: all, clean, fclean, re

all: $(NAME)

libftcomp:
	@echo "\033[31;5;mCompiling Printf...\033[0m"
	@make -C libft/

$(NAME): libftcomp  $(OBJS) $(LIB)
	@libtool -static -o $(NAME) $(LIB) $(OBJS)
#	@echo "\033[31;3m\nCompiling Done !\033[0m"

$(OBJS): $(OBJS_PATH) $(SRCS) $(INCLUDES_PATH)
	@gcc -c $(SRCS)

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
#	@echo "\033[32;3mCleaning Done !\n\033[0m"

fclean: clean
	@echo "\033[32;5mFcleaning..."
	@make fclean -C libft/
	@rm -f $(NAME)
#	@echo "\033[32;3mFcleaning Done !\n\033[0m"

re: fclean all
