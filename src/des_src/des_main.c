
#include "ft_ssl_md5.h"


int		is_des_command(char *command)
{
	if (!ft_strcmp(command, "des"))
		return (1);
	// else if (!ft_strcmp(command, "sha256"))
	// 	return (1);
	return (0);
}

unsigned char hex_to_num(char hex)
{
	if (hex >= '0' && hex <= '9')
		return hex - '0';
	if (hex>= 'A' && hex <= 'F')
		return hex - 'A' + 10;
	if (hex >= 'a' && hex <= 'f')
		return hex - 'a' + 10;
	return 0; // to do: handle errors
}

void des_parse_key(unsigned char *dest, char *source)
{
	int i;

	ft_bzero(dest, 8);
	i = 0;
	while (i < 8)
	{
		dest[i] = hex_to_num(source[i * 2]) << 4;
		dest[i] |= hex_to_num(source[i * 2 + 1]);
		i++;
	}
}

void des_parse_security_flags(char **argv, t_des_flags *flags)
{
		if (!ft_strcmp("-k", *argv))
			des_parse_key(flags->key, *(argv + 1));
		else if (!ft_strcmp("-p", *argv))
			flags->pass = *(argv + 1);
		else if (!ft_strcmp("-s", *argv))
			flags->salt = *(argv + 1);
		else if (!ft_strcmp("-v", *argv))
			flags->i_vector = *(argv + 1);
		else
			flags->salt = **((char***)0); // assert(false) todo: delete
}

void des_parse_flags(t_des_flags *flags, int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc)
	{
		if (!ft_strcmp("-a", *argv))
			flags->use_base64 = 1;
		else if (!ft_strcmp("-d", *argv))
			flags->decrypt = 1;
		else if (!ft_strcmp("-e", *argv))
			flags->decrypt = 0;
		else if (++i == argc)
			exit_error_unknown_flag(*argv);
		else if (!ft_strcmp("-i", *argv))
			flags->input_file = *(++argv);
		else if (!ft_strcmp("-o", *argv))
			flags->output_file = *(++argv);
		else if (!ft_strcmp("-k", *argv) || !ft_strcmp("-p", *argv) ||
					!ft_strcmp("-s", *argv) || !ft_strcmp("-v", *argv))
			des_parse_security_flags(argv++, flags);
		else
			exit_error_unknown_flag(*argv);
		i++;
		argv++;
	}
}


void	exe_des_command(int argc, char **argv)
{
	t_des_flags		flags;
	char			*command;

	ft_bzero((void*)&flags, sizeof(t_des_flags));
	flags.command = *argv;
	argv++;
	argc--;
	des_parse_flags(&flags, argc, argv);
	des_work(&flags);
}


