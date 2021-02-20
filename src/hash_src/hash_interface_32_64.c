
#include "ft_ssl_md5.h"

void round_32(hash *h, uint32_t *memory, int round_num)
{
    return h->vtable->round_32(h, memory, round_num);
}

void prepare_block_32(hash *h, uint32_t *block, void *data)
{
    return h->vtable->prepare_block_32(block, data);
}

void round_64(hash *h, uint64 *memory, int round_num)
{
    return h->vtable->round_64(h, memory, round_num);
}

void prepare_block_64(hash *h, uint64 *block, void *data)
{
    return h->vtable->prepare_block_64(block, data);
}