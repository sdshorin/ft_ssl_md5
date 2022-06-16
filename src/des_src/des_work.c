



#include "ft_ssl_md5.h"

#include <stdio.h>






void des_work(t_des_flags *flags)
{
	t_des_env env;

	ft_bzero((void*)&env, sizeof(t_des_env));
	des_init_env(&env, flags);
	des_init_salt(&env, flags);

	if (flags->key_inited)
		ft_memcpy(env.key, flags->key, 8);
	else
		des_make_key(&env, flags);
	if (flags->iv_inited)
		ft_memcpy((unsigned char*) &env.i_vector, flags->i_vector, 8);
	else if (env.mode & DES_CBC_MODE && !env.i_vector)
		exit_error("Miss -v param\n");
	if (flags->verbpose)
	{
		printf("salt: "); uint64_to_hex(*(uint64_t*)flags->salt);
		printf("key: ");  uint64_to_hex(*(uint64_t*)env.key);
		printf("i_vector: ");  uint64_to_hex(env.i_vector);

	}
	des_create_keys(&env);
	des_stream(&env);
}


void des_process_stream_block(t_des_env *env, unsigned char *buff)
{
	int i;

	uint64_t encrypted_8_byte;

	i = 0;
	while (i * 8 < BASE_DES_BLOCK_SIZE)
	{
		encrypted_8_byte = process_des_block(env, *(uint64_t*)(buff + i * 8));
		ft_memcpy(buff + i * 8, (void*)&encrypted_8_byte, 8);
		i += 1;
	}
	env->write(env->fd_out, buff, BASE_DES_BLOCK_SIZE, NEED_NEXT_LINE);
}


void des_process_last_stream_block(t_des_env *env, unsigned char *buff, size_t size)
{
	// char	out_buff[(BASE64_BLOCK_SIZE + 9)/3*4];
	int i;
	uint64_t encrypted_8_byte;

	i = 0;
	if (!env->decrypt)
	{
		size = des_add_padding(buff, size);
	}
	while (i * 8 < (int)size)
	{
		encrypted_8_byte = process_des_block(env, *(uint64_t*)(buff + i * 8));
		ft_memcpy(buff + i * 8, (void*)&encrypted_8_byte, 8);
		i += 1;
	}
	if (env->decrypt)
	{
		size = des_remove_padding(buff, size);
	}

	env->write(env->fd_out, buff, size, LAST_BLOCK | NEED_NEXT_LINE);
}


void	des_stream(t_des_env *env)
{
	unsigned char	current[BASE_DES_BLOCK_SIZE + 8];
	unsigned char	next_block[BASE_DES_BLOCK_SIZE + 8];
	int		current_read;
	int		next_read;
	int		i;

	current_read = env->read(env->fd_in, current, BASE_DES_BLOCK_SIZE);
	next_read = env->read(env->fd_in, next_block, BASE_DES_BLOCK_SIZE);
	while (next_read > 0)
	{
		des_process_stream_block(env, current);
		ft_memcpy(current, next_block, next_read);
		current_read = next_read;
		next_read = env->read(env->fd_in, next_block, BASE_DES_BLOCK_SIZE);
	}
	i = current_read;
	while(i < BASE_DES_BLOCK_SIZE + 8)
		current[i++] = '\0';
	des_process_last_stream_block(env, current, current_read);
}



