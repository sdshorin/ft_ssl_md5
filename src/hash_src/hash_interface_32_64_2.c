
#include "ft_ssl_md5.h"

void _process_block(hash *hash, void *data)
{
    if (hash->vtable->_process_block_32)
        return hash->vtable->_process_block_32(hash, data);
    return hash->vtable->_process_block_64(hash, data);
}

int create_last_block(hash *hash, void **data, int block_size)
{
    if (hash->vtable->create_last_block_32)
        return hash->vtable->create_last_block_32(hash, data, block_size);
    return hash->vtable->create_last_block_64(hash, data, block_size);
}
