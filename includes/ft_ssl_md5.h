
#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "libft.h"
#include <fcntl.h>
# include "hash.h"


typedef struct hash_flags {
	unsigned char p_flag;
	unsigned char q_flag;
	unsigned char r_flag;
	unsigned char s_flag;
	unsigned char flags_parsed;
	unsigned char printed_hash_from_input;
	char *command;
} hash_flags;


hash *factory_get_hash(char *command);
void print_hash(char* hash, char *source, hash_flags *flags, int is_file);
// int is_32_hash(char *hash_name);
int is_hash_command(char *command);


void print_hash_from_string(char *command, hash_flags *flags, char *str);
void print_hash_from_file(char *command, hash_flags *flags, char *file_path);
void print_hash_from_input(char *command, hash_flags *flags);


void print_unexpected_arg();
void exit_error_no_string();
void exit_error_unknown_flag(char *flag);

#endif