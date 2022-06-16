
.PHONY: all clean fclean re

NAME = ft_ssl
NAME_LIBFT = libft.a

LIBFT = $(addprefix $(LIBFT_DIR),$(NAME_LIBFT))

SRC_DIR = ./src/
HASH_SRC_DIR = ./src/hash_src/
BASE64_SRC_DIR = ./src/base64_src/
DES_SRC_DIR = ./src/des_src/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/
LFT = -L $(LIBFT_DIR) -lft

HASH_SRCS_LIST = hash_from_source.c sha256_base.c factory.c \
factory_2.c sha256_utils.c hash_interface.c md5_base.c sha512_base.c \
hash_interface_32_64.c md5_utils.c  hash_loop_32_64.c \
hash_interface_32_64_2.c print_hash.c hash_main.c sha2.c exe_hash_command.c

BASE64_LIST = base64_decode_from_source.c base64_encode_from_source.c \
base64_encode_process.c exe_base64_command.c

DES_LIST = des_main.c des_work.c des_round.c des_io.c des_keys.c des_init.c \
des_tools.c des_flags_utils.c

SRCS_LIST = main.c utils.c exeptions.c tests.c
HEADERS_LIST = ft_ssl_md5.h hash.h des.h utils.h

SRCS = $(addprefix $(SRC_DIR),$(SRCS_LIST)) \
$(addprefix $(HASH_SRC_DIR),$(HASH_SRCS_LIST)) \
$(addprefix $(BASE64_SRC_DIR),$(BASE64_LIST)) \
$(addprefix $(DES_SRC_DIR),$(DES_LIST))

OBJS = $(SRCS:.c=.o)

INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

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
	@/bin/rm -f $(OBJS)
	@echo "Object files deleted"
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Executable files deleted"
	@make fclean -C $(LIBFT_DIR)

re: fclean all