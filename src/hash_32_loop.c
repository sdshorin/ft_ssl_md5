

#include "hash_32.h"




int create_last_block_32(hash32 *hash, void **data, int block_size)
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
        swipe_endian_long(&hash->data_sum_size);
    ft_memmove(filled_data + block_size + zero_append_size + 1, (void*)&hash->data_sum_size, 8);
    *data = filled_data;
    return (block_size + 1 + zero_append_size + 8);
}


void _process_block_32(hash32 *hash, void *data) // 64 byte block
{
    uint32_t block[64];
    int i;
    // hash32 *hash_copy;

	// hash_copy = hash-
    i = 0;
    copy_hash_32(hash->backup, hash);
	if (hash->prepare_block_before_round)
	{
		prepare_block_32(hash, block, data);
    	while (i < 64)
        	round_32(hash, block, i++);
	}
	else
		while (i < 64)
        	round_32(hash, (uint32_t*)data, i++); // change this 
      
    add_hash_32(hash, hash->backup);
	// print_hash(sha2);

    // return (sha2);
}






void proceed_block_32(hash32 *hash, void *data)
{
	hash->data_sum_size += 64;
	// add_data_size_32(hash, 64);
    _process_block_32(hash, data);
} 



void proceed_last_block_32(hash32 *hash, void *data, int block_size)
{
    int last_block_size;

    // sha2->data_sum_size += block_size;
	// add_data_size_32(hash, block_size)
	hash->data_sum_size += block_size;
    hash->data_sum_size *=8;
    last_block_size = create_last_block_32(hash, &data, block_size);
    if (last_block_size > 64)
    {
        _process_block_32(hash, data);
        _process_block_32(hash, data + 64);
    }
    else
        _process_block_32(hash, data);
    free(data);
    // return (sha2);
}




