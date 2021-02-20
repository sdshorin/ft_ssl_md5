


#include "ft_ssl_md5.h"


void print_usage()
{
	ft_putendl("usage: ft_ssl command [command opts] [command args]");
}


void init_hash_flags(hash_flags *flags) {
	flags->p_flag = 0;
	flags->q_flag = 0;
	flags->r_flag = 0;
	flags->s_flag = 0;
	flags->printed_hash_from_input = 0;
	flags->flags_parsed = 0;
}

void print_hash_from_command_line_p(char *command, hash_flags *flags)
{
	flags->p_flag = 1;
	flags->printed_hash_from_input = 1;
	print_hash_from_input(command, flags);
}

int work_with_flags(char *command, hash_flags *flags, int argc, char **argv)
{
	int i;

	i = 0;
	while (i < argc && **argv == '-')
	{
		if (!ft_strcmp("-q", *argv))
			flags->q_flag = 1;
		else if (!ft_strcmp("-r", *argv))
			flags->r_flag = 1;
		else if (!ft_strcmp("-p", *argv))
			print_hash_from_command_line_p(command, flags);
		else if (!ft_strcmp("-s", *argv))
			if (++i == argc)
				exit_error_no_string();
			else
			{
				print_hash_from_string(command, flags, *(++argv));
				flags->printed_hash_from_input = 1;
			}
		else
			exit_error_unknown_flag(*argv);
		i++;
		argv++;
	}
	return (i);
}


void exe_hash_command(int argc, char **argv)
{
	hash_flags flags;
	char *command;
	int commands_offset;
	
	init_hash_flags(&flags);
	command = *argv;
	flags.command = command;
	argv++;
	argc--;
	commands_offset = work_with_flags(command, &flags, argc, argv);
	argv += commands_offset;
	argc -= commands_offset;
	while (argc)
	{
		print_hash_from_file(command, &flags, *argv);
		argv++;
		argc--;
		flags.printed_hash_from_input = 1;
	}
	if (!flags.printed_hash_from_input)
		print_hash_from_input(command, &flags);
}

int main(int argc, char **argv){
	if (argc < 2)
		print_usage();
	else if (is_hash_command(argv[1]))
		exe_hash_command(argc - 1, argv + 1);
	else
		print_unexpected_arg(argv[1]);
}


