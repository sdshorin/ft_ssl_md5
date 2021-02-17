


#include "hash_32.h"


void round_32 (hash32 *h, uint32_t *memory, int round_num) { return h->vtable->round(h, memory, round_num); }
void prepare_block_32 (hash32 *h, uint32_t *block, void *data) { return h->vtable->prepare_block(block, data); }
void copy_hash_32 (hash32* copy, hash32* source) { return copy->vtable->copy_hash(copy, source); }
void add_hash_32 (hash32* base, hash32* to_add) { return base->vtable->add_hash(base, to_add); }
char *hash_to_string_32 (hash32* h) { return h->vtable->hash_to_string(h); }

