
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

void des_parse_hex(unsigned char *dest, char *source)
{
	int i;

	ft_bzero(dest, 8);
	i = 0;
	while (i < 8)
	{
		if (!source[i * 2] || !source[i * 2 + 1]) {
			break;
		}
		dest[i] = hex_to_num(source[i * 2]) << 4;
		dest[i] |= hex_to_num(source[i * 2 + 1]);
		++i;
	}
}


void check_flag_param(char *str)
{
	if(!str)
		exit_error("empty flag");
}

void des_parse_security_flags(char **argv, t_des_flags *flags)
{
		if (!ft_strcmp("-k", *argv))
		{
			check_flag_param(*(argv + 1));
			des_parse_hex(flags->key, *(argv + 1));
			flags->key_inited = 1;
		}
		else if (!ft_strcmp("-p", *argv))
		{
			check_flag_param(*(argv + 1));
			ft_strncpy(flags->pass, *(argv + 1), _PASSWORD_LEN + 1);
			flags->pass_inited = 1;
		}
		else if (!ft_strcmp("-s", *argv))
		{
			check_flag_param(*(argv + 1));
			des_parse_hex(flags->salt, *(argv + 1));
			flags->salt_inited = 1;
		}
		else if (!ft_strcmp("-v", *argv))
		{
			check_flag_param(*(argv + 1));
			des_parse_hex(flags->i_vector, *(argv + 1));
			flags->iv_inited = 1;
		}
}

void des_parse_files_flags(char **argv, t_des_flags *flags)
{
	check_flag_param(*(argv + 1));
	if (!ft_strcmp("-i", *argv))
		flags->input_file = *(argv + 1);
	else if (!ft_strcmp("-o", *argv))
		flags->output_file = *(argv + 1);
}

void des_parse_flags(t_des_flags *flags, int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc)
	{
		if (!ft_strcmp("-a", *argv))
			flags->use_base64 = 1;
		else if (!ft_strcmp("-V", *argv))
			flags->verbpose = 1;
		else if (!ft_strcmp("-d", *argv))
			flags->decrypt = 1;
		else if (!ft_strcmp("-e", *argv))
			flags->decrypt = 0;
		else if (++i == argc)
			exit_error_unknown_flag(*argv);
		else if (!ft_strcmp("-i", *argv) || !ft_strcmp("-o", *argv))
			des_parse_files_flags(argv++, flags);
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


