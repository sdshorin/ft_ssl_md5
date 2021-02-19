


#include "hash.h"

void copy_hash(hash* copy, hash* source) { return copy->vtable->copy_hash(copy, source); }
void add_hash (hash* base, hash* to_add) { return base->vtable->add_hash(base, to_add); }
char *hash_to_string (hash* h) { return h->vtable->hash_to_string(h); }

