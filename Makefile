
.PHONY: all clean fclean re

NAME = ft_ssl
NAME_LIBFT = libft.a

LIBFT = $(addprefix $(LIBFT_DIR),$(NAME_LIBFT))

SRC_DIR = ./src/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/
LFT = -L $(LIBFT_DIR) -lft

SRCS_LIST = main.c factory.c hash_32_loop.c sha256_utils.c \
hash_32_interface.c hash_32_main.c sha256_base.c utils.c \
md5_base.c md5_utils.c exeptions.c hash_work.c print_hash.c \
sha2.c
HEADERS_LIST = ft_ssl_md5.h hash_32.h

SRCS = $(addprefix $(SRC_DIR),$(SRCS_LIST))

OBJS = $(SRCS:.c=.o)

INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR)

CC = gcc
CFLAGS = -g #-Wall -Wextra -Werror -g

all: $(NAME)

%.o: %.c $(addprefix $(INC_DIR),$(HEADERS_LIST))
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
	@echo ".\c"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(LFT) $(INCLUDES) $(OBJS) -o $(NAME)
	@echo "$(NAME_PS) executable created"

# $(NAME_CH): $(LIBFT) $(OP_OBJS) $(CH_OBJS)
# 	@$(CC) $(CFLAGS) $(LFT) $(INCLUDES) $(OP_OBJS) $(CH_OBJS) -o $(NAME_CH)
# 	@echo "$(NAME_CH) executable created"

FORCE: ;

$(LIBFT): FORCE
	@make -C $(LIBFT_DIR)

clean:
	@/bin/rm -f $(OBJS) $(OBJS) $(OBJS)
	@echo "Object files deleted"
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Executable files deleted"
	@make fclean -C $(LIBFT_DIR)

re: fclean all