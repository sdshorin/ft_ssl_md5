
// #include "hash.h"
# include "ft_ssl_md5.h"


int md5_get_data_num(round_num) {
    if (round_num < 16)
        return (round_num);
    if (round_num < 32)
        return (((round_num)*5 + 1) % 16);
    if (round_num < 48)
        return (((round_num)*3 + 5) % 16);
    return (((round_num)*7) % 16);
}




char *md5_hash_to_string(hash *md5_p)
{
    char *hash_str;
    md5_hash *md5;

    md5 = (md5_hash*)md5_p;
    hash_str = ft_memalloc(33);
    if (!hash_str)
        exit(1);
    uint32_to_hash(md5_p, hash_str, md5->a);
    uint32_to_hash(md5_p, hash_str + 8, md5->b);
    uint32_to_hash(md5_p, hash_str + 16, md5->c);
    uint32_to_hash(md5_p, hash_str + 24, md5->d);
    return hash_str;
}



void md5_add_hash(hash *hash_base, hash *hash_to_add)
{
	md5_hash *hash;
	md5_hash *to_add;
	hash = (md5_hash*)hash_base;
	to_add = (md5_hash*)hash_to_add;

    hash->a += to_add->a;
    hash->b += to_add->b;
    hash->c += to_add->c;
    hash->d += to_add->d;
}

void md5_copy_hash(hash* hash_base, hash *source_base)
{
	md5_hash *hash_copy;
	md5_hash *source;

	hash_copy = (md5_hash*)hash_base;
	source = (md5_hash*)source_base;
    hash_copy->a = source->a;
    hash_copy->b = source->b;
    hash_copy->c = source->c;
    hash_copy->d = source->d;
}

void md5_round(hash *hash, uint32_t *memory, int round_num)
{
    md5_hash *round;
    int s;

    round = (md5_hash*)hash;
    s = md5_get_byte_rotation(round_num);
    if (round_num < 16)
        round->a += F(round->b, round->c, round->d);
    else if (round_num < 32)
        round->a += G(round->b, round->c, round->d);
    else if (round_num < 48)
        round->a += H(round->b, round->c, round->d);
    else
        round->a += I(round->b, round->c, round->d);
    round->a += memory[md5_get_data_num(round_num)] + md5_get_T(round_num);

    round->a = ROTATEL(round->a, s);
    round->a += round->b;
    md5_rotate_reg(round);
}

