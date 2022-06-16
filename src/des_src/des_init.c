#include "ft_ssl_md5.h"





void des_init_env(t_des_env *env, t_des_flags *flags)
{
	if (flags->input_file)
		env->fd_in = open_file(flags->input_file, O_RDONLY);
	else
		env->fd_in = 0;
	if (flags->output_file)
		env->fd_out = open_file(flags->output_file, O_WRONLY | O_CREAT | O_TRUNC);
	else
		env->fd_out = 1;

	env->use_base64 = flags->use_base64;
	env->decrypt = flags->decrypt;
	if (env->use_base64 && !env->decrypt)
		env->write = write_base64;
	else
		env->write = write_wrapper;
	if (env->use_base64 && env->decrypt)
		env->read = read_wrapper_decode_base_64;

	else
		env->read = nostop_read;
	env->mode = 0;
	if (!ft_strcmp(flags->command, "des-cbc")) {
		env->mode |= DES_CBC_MODE;
	}

}


void des_init_salt(t_des_env *env, t_des_flags *flags)
{
	if (!flags->key_inited)
	{
		if (flags->decrypt)
		{
			read_salt(env, flags);
		}
		else
		{
			if (!flags->salt_inited)
				des_get_salt(flags->salt);
			print_salt_to_file(env, flags);
		}
	}
}



void read_salt(t_des_env *env, t_des_flags *flags)
{

	char decoded_buff[17];
	int i;

	i = env->read(env->fd_in, decoded_buff, 16);
	if (i != 16)
		exit_error("file invalid");
	decoded_buff[16] = 0;
	if (ft_strncmp("Salted__", decoded_buff, 8))
		exit_error("file invalid");
	ft_memcpy(flags->salt, decoded_buff + 8, 8);
	env->data_offset = 16;
}

