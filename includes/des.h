
# include "libft.h"

typedef struct s_des_env t_des_env;

struct s_des_env {
	unsigned char	a;
	unsigned char	d;
	unsigned char	*key;
	unsigned char	*pass;
	unsigned char	*salt;
	int				fd_in;
	int				fd_out;
	uint64_t		round_key[16];
} ;


typedef struct s_des_flag t_des_flags;

struct s_des_flag {
	unsigned char	a;
	unsigned char	d;
	char			*input_file;
	char			*output_file;
	char			*key;
	char			*pass;
	char			*salt;
	char			*i_vector;
	char			*command;
};

#define DES_ROT_KEY(x, rot) ((x >> rot) | (x << (28 - rot)))


int		is_des_command(char *command);
void	exe_des_command(int argc, char **argv);
void des_print_block(uint64_t encrypted_block, t_des_env *env);


void des_work(t_des_flags *flags);
