
# include "ft_ssl_md5.h"



int is_32_hash(char *hash_name)
{
    if (!ft_strcmp(hash_name, "md5"))
		return (1);
	else if (!ft_strcmp(hash_name, "sha256"))
		return (1);
	return (0);
}


int is_hash_command(char *command)
{
	if (!ft_strcmp(command, "md5"))
		return (1);
	else if (!ft_strcmp(command, "sha256"))
		return (1);
	return (0);
}


void print_str_hash(char *command, hash_flags *flags, char *str)
{
	hash32 *hash;
	char *hash_str;
	hash = factory_get_hash(command);
	if (is_32_hash(command))
		hash_str = get_hash_from_string_32(hash, str);

	print_hash(hash_str, str, flags, 0);

	free(hash);
	free(hash_str);
}


void print_file_hash(char *command, hash_flags *flags, char *file_path)
{
	int fd;
	hash32 *hash;
	char *hash_str;

	fd = open(file_path, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
	{
		ft_putstr("Cannot open file ");
		ft_putendl(file_path);
		return ;
	}
	hash = factory_get_hash(command);
	if (is_32_hash(command))
		hash_str = get_hash_from_file_32(hash, fd);
	print_hash(hash_str, file_path, flags, 1);
	free(hash);
	free(hash_str);
}







char *read_string_from_input()
{
	char *temp_str;
	char *input_str;
	char buffer[129];

	input_str = 0;
	ft_bzero(buffer, 129);
	while (read(0, buffer, 128) > 0)
	{
		temp_str = input_str;
		if (input_str)
			input_str = ft_strjoin(input_str, buffer);
		else
			input_str = ft_strdup(buffer);
		if (!input_str)
			exit(1);
		if (temp_str)
			free(temp_str);
		ft_bzero(buffer, 129);
	}
	return (input_str);
}

void print_hash_from_input(char *command, hash_flags *flags)
{
	hash32 *hash;
	char *input_str;
	char *hash_str;

	input_str = read_string_from_input();
	hash = factory_get_hash(command);
	if (is_32_hash(command))
		hash_str = get_hash_from_file_32(hash, 0);
	if (flags->q_flag)
		ft_putendl(input_str);
	ft_putendl(hash_str);
	free(hash);
	free(hash_str);
	free(input_str);
}
