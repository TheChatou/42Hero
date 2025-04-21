#include "emb.h"

void    ft_memset(uint8_t *s, uint16_t len, uint8_t byte)
{
    for(uint16_t i = 0; i < len; i++)
    {
        s[i] = byte;
    }
}
uint8_t ft_strcmp(char *a, char *b)
{
    while (*a && *b)
    {
        if ((uint8_t)*a != (uint8_t)*b)
            break;
        a++;
        b++;
    }
    return ((uint8_t)*a - (uint8_t) *b);
}
uint16_t   ft_strlen(char *s)
{
    uint16_t    i = 0;
    while(s[i])
        i++;
    return (i);
}

uint8_t ft_memcmp(uint8_t *a, uint8_t *b, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++)
    {
        if (a[i] != b[i])
            return (1);
    }
    return (0);
}

void    ft_memcpy(uint8_t *dest, uint8_t *src, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++)
    {
        dest[i] = src[i];
    }
}