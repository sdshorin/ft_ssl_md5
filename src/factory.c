

#include "ft_ssl_md5.h"


hash32 *sha256_create() {
    static const virtual_table vtable = {
        sha256_round, sha256_prepare_block, sha256_copy_hash,
        sha256_add_hash, sha256_hash_to_string
    };
    static hash32 base = { &vtable, 0, TYPE_SHA_256, 1, 1, 1, 0 };

    sha256_hash *sha2 = (sha256_hash*)malloc(sizeof(sha256_hash));
    sha256_hash *backup = (sha256_hash*)malloc(sizeof(sha256_hash));
	if (!sha2 || !backup)
		exit(1);
    ft_memcpy(&sha2->base, &base, sizeof(base));
    ft_memcpy(&backup->base, &base, sizeof(base));
	sha2->h0 = 0x6a09e667;
	sha2->h1 = 0xbb67ae85;
	sha2->h2 = 0x3c6ef372;
	sha2->h3 = 0xa54ff53a;
	sha2->h4 = 0x510e527f;
	sha2->h5 = 0x9b05688c;
	sha2->h6 = 0x1f83d9ab;
	sha2->h7 = 0x5be0cd19;
	sha2->base.backup = (hash32*)backup;
    return &sha2->base;
}


hash32 *sha224_create() {
    static const virtual_table vtable = {
        sha256_round, sha256_prepare_block, sha256_copy_hash,
        sha256_add_hash, sha224_hash_to_string
    };
    static hash32 base = { &vtable, 0, TYPE_SHA_224, 1, 1, 1, 0 };

    sha256_hash *sha2 = (sha256_hash*)malloc(sizeof(sha256_hash));
    sha256_hash *backup = (sha256_hash*)malloc(sizeof(sha256_hash));
	if (!sha2 || !backup)
		exit(1);
    ft_memcpy(&sha2->base, &base, sizeof(base));
    ft_memcpy(&backup->base, &base, sizeof(base));
	sha2->h0 = 0xC1059ED8;
	sha2->h1 = 0x367CD507;
	sha2->h2 = 0x3070DD17;
	sha2->h3 = 0xF70E5939;
	sha2->h4 = 0xFFC00B31;
	sha2->h5 = 0x68581511;
	sha2->h6 = 0x64F98FA7;
	sha2->h7 = 0xBEFA4FA4;
	sha2->base.backup = (hash32*)backup;
    return &sha2->base;
}

hash32 *md5_create() {
    static const virtual_table vtable = {
        md5_round, 0, md5_copy_hash,
        md5_add_hash, md5_hash_to_string
    };
    static hash32 base = { &vtable, 0, TYPE_MD5, 0, 0, 0, 0 };

    md5_hash *md5 = (md5_hash*)malloc(sizeof(md5_hash));
    md5_hash *backup = (md5_hash*)malloc(sizeof(md5_hash));
	if (!md5 || !backup)
		exit(1);
    ft_memcpy(&md5->base, &base, sizeof(base));
    ft_memcpy(&backup->base, &base, sizeof(base));
	md5->a = 0x67452301;
    md5->b = 0xefcdab89;
    md5->c = 0x98badcfe;
    md5->d = 0x10325476;
	md5->base.backup = (hash32*)backup;
    return &md5->base;
}



hash32 *factory_get_hash(char *command)
{
    if (!ft_strcmp(command, "md5"))
		return (md5_create());
	else if (!ft_strcmp(command, "sha256"))
		return (sha256_create());
    else if (!ft_strcmp(command, "sha224"))
		return (sha224_create());
	return (md5_create());
}


