
#include "ft_ssl_md5.h"

void print_unexpected_arg(char* arg)
{
	ft_putstr("ft_ssl: Error: ");
	ft_putstr(arg);
	ft_putstr(" is an invalid command.");
	ft_putendl("Standard commands:");
	ft_putendl("Message Digest commands:");
	ft_putendl("md5 sha256 sha224 sha512 sha384 sha512/256 ");
	ft_putendl("Cipher commands:");
	ft_putendl("-p, -q, -r, -s");
}

void exit_error_no_string()
{
	ft_putendl("Error: no string after -s flag");
	exit(1);
}

void exit_error_unknown_flag(char *flag)
{
	ft_putstr("Error: unknown flag ");
	ft_putendl(flag);
	exit(1);
}
