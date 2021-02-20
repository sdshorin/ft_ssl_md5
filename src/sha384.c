
#include "ft_ssl_md5.h"



char *sha384_hash_to_string(hash *hash_base)
{
    char *hash_str;
    int i;
	sha512_hash *hash;

    i = 0;
	hash = (sha512_hash*) hash_base;
    hash_str = ft_memalloc(97); // защита!!!!
	if (!hash_str)
		exit(1);
     uint64_to_hash(hash_base, hash_str, hash->h0);
     uint64_to_hash(hash_base, hash_str + 16, hash->h1);
     uint64_to_hash(hash_base, hash_str + 32, hash->h2);
     uint64_to_hash(hash_base, hash_str + 48, hash->h3);
     uint64_to_hash(hash_base, hash_str + 64, hash->h4);
     uint64_to_hash(hash_base, hash_str + 80, hash->h5);
    return hash_str;
}