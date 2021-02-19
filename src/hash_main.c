
#include "ft_ssl_md5.h"


void proceed_block(hash *hash, void *data)
{
	hash->data_sum_size += hash->block_b;
    _process_block(hash, data);
} 


void proceed_last_block(hash *hash, void *data, int block_size)
{
    int last_block_size;

	hash->data_sum_size += block_size;
    hash->data_sum_size *=8;
    last_block_size = create_last_block(hash, &data, block_size);
    if (last_block_size > hash->block_b)
    {
        _process_block(hash, data);
        _process_block(hash, data + hash->block_b);
    }
    else
        _process_block(hash, data);
    free(data);
}



char *get_hash_from_string(hash *hash, char *str)
{
    int len;

    len = ft_strlen(str);
    while (len - hash->block_b > 0)
    {
        proceed_block(hash, (void*)str);
        len -= hash->block_b;
        str += hash->block_b;
    }
    proceed_last_block(hash, (void*)str, len);
    return (hash_to_string(hash));
}


char *get_hash_from_file(hash *hash, int fd)
{
    char			buff[128];
    int ch_read;
		
    while ((ch_read = read(fd, buff, hash->block_b)) == hash->block_b)
        proceed_block(hash, (void*)buff);
    proceed_last_block(hash, (void*)buff, ch_read);
    return (hash_to_string(hash));
}



