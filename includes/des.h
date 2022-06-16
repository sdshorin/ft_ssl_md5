
# include "libft.h"

#include <pwd.h>
#include <unistd.h>

typedef struct s_des_env t_des_env;

#define DES_CBC_MODE 1

struct s_des_env {
	unsigned char	use_base64;
	unsigned char	decrypt;
	unsigned char	key[8];
	uint64_t		i_vector;
	unsigned char	*pass;
	unsigned char	*salt;
	int				fd_in;
	int				fd_out;
	int				data_offset;
	int				mode;
	uint64_t		round_key[16];
	ssize_t	(*read)(int fd, void *buff, size_t size);
	ssize_t	(*write)(int fd, const void *buff, size_t size, int flags);

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
	unsigned char			verbpose;
	char			*command;
};

#define DES_ROT_KEY(x, rot) ((x >> rot) | (x << (28 - rot)))


#define LAST_BLOCK 1
#define NEED_NEXT_LINE 2

int		is_des_command(char *command);
void	exe_des_command(int argc, char **argv);



/*des_init.c*/
void des_init_env(t_des_env *env, t_des_flags *flags);
void des_init_salt(t_des_env *env, t_des_flags *flags);
void read_salt(t_des_env *env, t_des_flags *flags);
void des_get_salt(unsigned char *salt);


/*des_keys.c*/
void des_make_key(t_des_env *env, t_des_flags *flags);

/*des_round.c*/
uint64_t 	process_des_block(t_des_env *env, uint64_t crypto_8_byte);

/*des_io.c*/
ssize_t write_base64(int fd, const void *buff, size_t len, int flag);
ssize_t write_wrapper(int fd, const void *buff, size_t len, int flag);
ssize_t read_wrapper_decode_base_64(int fd, void *out_buff, size_t size);
ssize_t nostop_read(int fd, void *out_buff, size_t buff_size);

/*des_tools.c*/
size_t des_add_padding(unsigned char *buff, size_t size);
size_t des_remove_padding(unsigned char *buff, size_t size);
uint64_t permutation(uint64_t block, int *premut_table, int size);
void print_salt_to_file(t_des_env *env, t_des_flags *flags);



void	des_stream(t_des_env *env);
void des_parse_hex(unsigned char *dest, char *source);

ssize_t write_lines(int fd, const void *buff, size_t len, size_t block_size);

void des_work(t_des_flags *flags);
