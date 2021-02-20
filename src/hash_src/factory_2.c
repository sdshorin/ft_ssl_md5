

#include "ft_ssl_md5.h"

hash *sha512_256_create() {
    static const virtual_table vtable = {
        0, sha512_round, 0, sha512_prepare_block, sha512_copy_hash,
        sha512_add_hash, sha512_256_hash_to_string, 0, _process_block_64,
        0, create_last_block_64
    };
    static hash base = { &vtable, 0, TYPE_SHA_512_256 , 1, 1, 1, 128, 0 };

    sha512_hash *sha2 = (sha512_hash*)malloc(sizeof(sha512_hash));
    sha512_hash *backup = (sha512_hash*)malloc(sizeof(sha512_hash));
	if (!sha2 || !backup)
		exit(1);
    ft_memcpy(&sha2->base, &base, sizeof(base));
    ft_memcpy(&backup->base, &base, sizeof(base));
	sha2->h0 = 0x22312194FC2BF72C;
	sha2->h1 = 0x9F555FA3C84C64C2;
	sha2->h2 = 0x2393B86B6F53B151;
	sha2->h3 = 0x963877195940EABD;
	sha2->h4 = 0x96283EE2A88EFFE3;
	sha2->h5 = 0xBE5E1E2553863992;
	sha2->h6 = 0x2B0199FC2C85B8AA;
	sha2->h7 = 0x0EB72DDC81C52CA2;
	sha2->base.backup = (hash*)backup;
    return &sha2->base;
}
