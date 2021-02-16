# include "ft_ssl_md5.h"


void print_hash_type(char *type)
{
	while (*type)
		write(1, ft_toupper(*type++), 1);
}

void print_source(char *source, int is_file)
{
	if (!is_file)
		write(1, "\"", 1);
	ft_putstr(source);
	if (!is_file)
		write(1, "\"", 1);
}


void print_hash(char* hash, char *source, hash_flags *flags, int is_file)
{
	if (!flags->q_flag && !flags->r_flag)
	{
		print_hash_type(flags->command);
		write(1, " (", 2);
		print_source(source, is_file);
		write(1, ") = ", 4);
		ft_putendl(hash);
	}
	else if (!flags->q_flag)
	{
		ft_putstr(hash);
		write(1, " ", 1);
		print_source(source, is_file);
		write(1, "\n", 1);
	}
	else
		ft_putendl(hash);
}

