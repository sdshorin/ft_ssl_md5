

#include "ft_ssl_md5.h"




int create_last_block_32(hash *hash, void **data, int block_size)
{
    void *filled_data;
    int zero_append_size;

    zero_append_size = (56 - (block_size + 1) % 64);
    if (zero_append_size < 0)
        zero_append_size += 64;
    filled_data = ft_memalloc(block_size + 1 + zero_append_size + 8);
    if (!filled_data)
        exit(1);
    ft_memmove(filled_data, *data, block_size);
    *(unsigned char*)(filled_data + block_size) = 0x80;
    if (hash->last_block_size_big_endian)
        swipe_endian_64(&hash->data_sum_size);
    ft_memmove(filled_data + block_size + zero_append_size + 1, (void*)&hash->data_sum_size, 8);
    *data = filled_data;
    return (block_size + 1 + zero_append_size + 8);
}


void _process_block_32(hash *hash, void *data) // 64 byte block
{
    uint32_t block[64];
    int i;

    i = 0;
    copy_hash(hash->backup, hash);
	if (hash->prepare_block_before_round)
	{
		prepare_block_32(hash, block, data);
    	while (i < 64)
        	round_32(hash, block, i++);
	}
	else
		while (i < 64)
        	round_32(hash, (uint32_t*)data, i++); // change this 
    add_hash(hash, hash->backup);
}






int create_last_block_64(hash *hash, void **data, int block_size)
{
    void *filled_data;
    int zero_append_size;

    zero_append_size = (120 - (block_size + 1) % 128);
    if (zero_append_size < 0)
        zero_append_size += 128;
    filled_data = ft_memalloc(block_size + 1 + zero_append_size + 8);
    if (!filled_data)
        exit(1);
    ft_memmove(filled_data, *data, block_size);
    *(unsigned char*)(filled_data + block_size) = 0x80;
    if (hash->last_block_size_big_endian)
        swipe_endian_64(&hash->data_sum_size);
    ft_memmove(filled_data + block_size + zero_append_size + 1, (void*)&hash->data_sum_size, 8);
    *data = filled_data;
    return (block_size + 1 + zero_append_size + 8);
}

void _process_block_64(hash *hash, void *data) // 64 byte block
{
    uint64 block[80];
    int i;

    i = 0;
    copy_hash(hash->backup, hash);
	if (hash->prepare_block_before_round)
	{
		prepare_block_64(hash, block, data);
    	while (i < 80)
        	round_64(hash, block, i++);
	}
	else
		while (i < 80)
        	round_64(hash, (uint64*)data, i++); // change this 
      
    add_hash(hash, hash->backup);
}






