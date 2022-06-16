

# include "libft.h"

void	reverse_byte_order_64(uint64_t *all_data_size);
void print_binary(uint64_t num);
void swipe_endian_bytes(unsigned char *all_data, int size);
void print_binary_32(uint32_t num);
void reverse_byte(unsigned char *byte);



int		is_test_command(char *command);
void tests();
// TODO: вынести в des
uint64_t 	process_des_ecb_block(t_des_env *env, uint64_t block);
void des_create_keys(t_des_env *env);

void	uint64_to_hex(uint64_t reg);
int assert_false(int line);
int open_file(char *path, int mode);

