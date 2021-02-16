
#include "ft_ssl_md5.h"



char *get_hash_from_string_32(hash32 *hash, char *str)
{
    int len;

    len = ft_strlen(str);
    while (len - 64 > 0)
    {
        proceed_block_32(hash, (void*)str);
        len -= 64;
        str += 64;
    }
    proceed_last_block_32(hash, (void*)str, len);
    return (hash_to_string_32(hash));
}


char *get_hash_from_file_32(hash32 *hash, int fd)
{
    char			buff[64];
    int ch_read;
		
    while ((ch_read = read(fd, buff, 64)) == 64)
        proceed_block_32(hash, (void*)buff);
    proceed_last_block_32(hash, (void*)buff, ch_read);
    return (hash_to_string_32(hash));
}



