
#include "hash_32.h"



char *get_hash_from_string_32(char *str)
{
    int len;
    hash32 *hash;


	hash = sha256_create();

    // sha2_init_buffer(&sha2);
    len = ft_strlen(str);
	// print_hash(&sha2);
    while (len - 64 > 0)
    {
        proceed_block_32(hash, (void*)str);
        len -= 64;
        str += 64;
    }
    proceed_last_block_32(hash, (void*)str, len);
	// print_hash(&sha2);
    return (hash_to_string_32(hash));
}



