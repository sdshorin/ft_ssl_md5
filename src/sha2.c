
# include "ft_ssl_md5.h"






char *sha224_hash_to_string(hash *hash_base)
{
    char *hash_str;
    int i;
	sha256_hash *hash;

    i = 0;
	hash = (sha256_hash*) hash_base;
    hash_str = ft_memalloc(57);
	if (!hash_str)
		exit(1);
    uint32_to_hash(hash_base, hash_str, hash->h0);
    uint32_to_hash(hash_base, hash_str + 8, hash->h1);
    uint32_to_hash(hash_base, hash_str + 16, hash->h2);
    uint32_to_hash(hash_base, hash_str + 24, hash->h3);
    uint32_to_hash(hash_base, hash_str + 32, hash->h4);
    uint32_to_hash(hash_base, hash_str + 40, hash->h5);
    uint32_to_hash(hash_base, hash_str + 48, hash->h6);
    // uint32_to_hash(hash_base, hash_str + 56, hash->h7);
    return hash_str;
}


