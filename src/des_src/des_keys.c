/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergey <sergey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 00:31:26 by sergey            #+#    #+#             */
/*   Updated: 2022/06/17 00:33:25 by sergey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

int		g_key_init_premutation[56] = {
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

int		g_des_key_rot[16] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

int		g_key_compress[56] = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

void	des_create_keys(t_des_env *env)
{
	uint32_t	c;
	uint32_t	d;
	uint64_t	temp;
	int			i;

	i = 0;
	temp = *(uint64_t *)env->key;
	swipe_endian_bytes((unsigned char *)&temp, 8);
	temp = permutation(temp, g_key_init_premutation, 56);
	c = ((uint32_t)temp << 4) >> 4;
	d = (uint32_t)(temp >> 28);
	while (i < 16)
	{
		c = (DES_ROT_KEY(c, g_des_key_rot[i]) << 4) >> 4;
		d = (DES_ROT_KEY(d, g_des_key_rot[i]) << 4) >> 4;
		temp = (uint64_t)c | (((uint64_t)d) << 28);
		temp = permutation(temp, g_key_compress, 56);
		env->round_key[i] = temp;
		i++;
	}
}

void	des_get_pass(char *pass)
{
	char	pass_first[_PASSWORD_LEN + 1];
	char	pass_second[_PASSWORD_LEN + 1];

	ft_strcpy(pass_first, getpass("enter des encryption password:"));
	ft_strcpy(pass_second, getpass(
			"Verifying - enter des-ecb encryption password:"));
	if (ft_strcmp(pass_first, pass_second))
		exit_error("Verify failure\nbad password read");
	ft_strcpy(pass, pass_first);
}

void	des_get_salt(unsigned char *salt)
{
	int		fd;
	char	c;
	int		i;

	i = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		exit_error("Can't open random stream");
	while (i < 8)
	{
		if (read(fd, &c, 1) != 1)
			exit_error("Can't read random bytes");
		if (' ' < c && c < 127)
			salt[i++] = c;
	}
}

void	des_make_key(t_des_env *env, t_des_flags *flags)
{
	char	salted_pass[_PASSWORD_LEN + 8 + 1];
	size_t	salted_len;
	t_hash	*hash_obj;
	char	*hash;

	if (!flags->pass_inited)
		des_get_pass(flags->pass);
	salted_len = ft_strlen(flags->pass);
	ft_bzero(salted_pass, _PASSWORD_LEN + 8 + 1);
	ft_memcpy(salted_pass, flags->pass, salted_len);
	ft_memcpy(salted_pass + salted_len, flags->salt, 8);
	salted_len += 8;
	salted_pass[salted_len] = 0;
	hash_obj = factory_get_hash_obj("sha256");
	hash = get_hash_from_mem(hash_obj, salted_pass, salted_len);
	des_parse_hex(env->key, hash);
	des_parse_hex((unsigned char *)&env->i_vector, hash + 16);
	free(hash);
	free(hash_obj);
}
