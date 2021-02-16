


# include "libft.h"
#include <fcntl.h>
# include "hash_32.h"


typedef struct hash_flags {
	unsigned char p_flag;
	unsigned char q_flag;
	unsigned char r_flag;
	unsigned char s_flag;
	unsigned char flags_parsed;
	unsigned char print_hash_from_input;
	char *command;
} hash_flags;

void hexDump(void *addr, int len);

hash32 *factory_get_hash(char *command);
void print_hash(char* hash, char *source, hash_flags *flags, int is_file);
int is_32_hash(char *hash_name);
int is_hash_command(char *command);


void print_str_hash(char *command, hash_flags *flags, char *str);
void print_file_hash(char *command, hash_flags *flags, char *file_path);
void print_hash_from_input(char *command, hash_flags *flags);


void print_unexpected_arg();
void exit_error_no_string();
void exit_error_unknown_flag(char *flag);




