
# include "libft.h"

#include <pwd.h>
#include <unistd.h>

typedef struct s_des_env t_des_env;

struct s_des_env {
	unsigned char	use_base64;
	unsigned char	decrypt;
	unsigned char	key[8];
	unsigned char			i_vector[8];
	unsigned char	*pass;
	unsigned char	*salt;
	int				fd_in;
	int				fd_out;
	uint64_t		round_key[16];
	ssize_t	(*read)(int fd, void *buff, size_t size);
	ssize_t	(*write)(int fd, const void *buff, size_t size);

} ;

typedef struct s_des_flag t_des_flags;

struct s_des_flag {
	unsigned char	use_base64;
	unsigned char	decrypt;
	char			*input_file;
	char			*output_file;
	unsigned char			key[8];
	unsigned char			key_inited;
	char			pass[_PASSWORD_LEN + 1];
	unsigned char			pass_inited;
	unsigned char			salt[8];
	unsigned char			salt_inited;
	unsigned char			i_vector[8];
	unsigned char			iv_inited;
	char			*command;
};

#define DES_ROT_KEY(x, rot) ((x >> rot) | (x << (28 - rot)))


int		is_des_command(char *command);
void	exe_des_command(int argc, char **argv);
void des_print_block(uint64_t encrypted_block, t_des_env *env);
void	des_encrypt_stream(t_des_env *env);
void des_parse_hex(unsigned char *dest, char *source);


void des_work(t_des_flags *flags);
