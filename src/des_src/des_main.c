
#include "ft_ssl_md5.h"




void des_parse_security_flags(char **argv, t_des_flags *flags)
{
		if (!ft_strcmp("-k", *argv))
			flags->key = *(argv + 1);
		else if (!ft_strcmp("-p", *argv))
			flags->pass = *(argv + 1);
		else if (!ft_strcmp("-s", *argv))
			flags->salt = *(argv + 1);
		else if (!ft_strcmp("-v", *argv))
			flags->i_vector = *(argv + 1);
		else
			flags->salt = ***((char***)0); // assert(false) todo: delete
}

void des_parse_flags(t_des_flags *flags, int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc)
	{
		if (!ft_strcmp("-a", *argv))
			flags->a = 1;
		else if (!ft_strcmp("-d", *argv))
			flags->d = 1;
		else if (!ft_strcmp("-e", *argv))
			flags->d = 0;
		else if (++i == argc)
			exit_error_des(*argv);
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
	return (i);
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


