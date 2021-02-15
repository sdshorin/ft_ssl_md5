
#include "libft.h"

#include "hash_32.h"


void hexDump(void *addr, int len) 
{
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Output description if given.
    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf("  %s\n", buff);

            // Output the offset.
            printf("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf(" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) {
            buff[i % 16] = '.';
        } else {
            buff[i % 16] = pc[i];
        }

        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf("  %s\n", buff);
}





void uint32_to_hash(char *dest, uint32_t num)
{
    int i;
    char *hex_char;
    unsigned char *bytes;

    i = 0;
    hex_char = "0123456789abcdef";
    bytes = (unsigned char*)&num;
    uint32_t  *yyy= (uint32_t  *)bytes;

    while (i < 4)
    {
        unsigned char ttt = bytes[i];
        char check = bytes[3 - i] >> 4;
        char check2 = bytes[3 - i] & 0x0F;
		//// Печать с другого конца!!
        dest[i * 2] = hex_char[bytes[3 - i] >> 4];
        dest[i * 2+ 1] = hex_char[bytes[3 - i] & 0x0F];
        i++;
    }
}




void ft_swipe(unsigned char *a, unsigned char *b)
{
    if (*a == *b)
        return ;
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}


void swipe_endian_long(long unsigned int *all_data_size)
{
    unsigned char *data;
    data = (unsigned char*)all_data_size;

    ft_swipe(data, data + 7);
    ft_swipe(data + 1, data + 6);
    ft_swipe(data + 2, data + 5);
    ft_swipe(data + 3, data + 4);
}

void swipe_endian(uint32_t *all_data_size)
{
    unsigned char *data;
    data = (unsigned char*)all_data_size;

    ft_swipe(data, data + 3);
    ft_swipe(data + 1, data + 2);
}
