#include "emb.h"


/* 
EEAR == adress register
EEARH 1 bit adress => always to 0
EEARL 8 bits adress

EEDR == Data Register
the data read or to be writen 

EECR == Control register
bits 7/6 reserved
EEPM{0/1} => chose action
EERIR => allow interrupts
EEMPE enable write needs to be 1 then set EEPE within 4 clock cycles -> will trigger write
EEPE write enable
EERE read enable
*/

uint8_t value_b[33] = {0};
uint8_t key_b[81] = {0};

static uint8_t is_print(uint8_t byte)
{
    if (byte > 0x19 && byte < 0x7f)
        return (1);
    return (0);
}

uint8_t eeprom_write(uint16_t adress, uint8_t byte)
{
    if (adress > EEPROM_MAX)
        return (1);
    while(EECR & (1 << EEPE))
        ;
    EEAR = adress;
    EECR |= (1 << EERE);
    if (EEDR == byte)
        return (2);
    EEDR = byte;
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
    return (0);
}

uint8_t eeprom_read(uint16_t adress, uint8_t *byte)
{
    if (adress > EEPROM_MAX)
        return (1);
    while(EECR & (1 << EEPE))
        ;
    EEAR = adress;
    EECR |= (1 << EERE);
    *byte = EEDR;
    return (0);
}

// read a 16bits word as little endian
uint8_t eeprom_read_word(uint16_t adress, uint16_t *word)
{
    uint8_t byte = 0;
    *word = 0;
    if (eeprom_read(adress, &byte))
        return(1);
    *word |= byte;
    if (eeprom_read(adress+1, &byte))
        return(1);
    *word |= ((uint16_t)byte) << 8;
    return(0);
}

//write a 16 bits word as little endian
uint8_t eeprom_write_word(uint16_t adress, uint16_t word)
{
    if (eeprom_write(adress, (uint8_t)(word & 0x00ff)))
    return(1);
    if (eeprom_write(adress+1, word >> 8))
        return (1);
    return (0);   
}

uint8_t eeprom_write_vector(uint16_t adress, uint8_t *v, uint8_t len)
{
    if (adress + len - 1 > EEPROM_MAX)
        return (1);
    for (uint8_t i = 0; i < len; i++)
    {
        if(eeprom_write(adress + i, v[i]))
            return (len - i);
    }
    return (0);
}

uint8_t eeprom_read_vector(uint16_t adress, uint8_t *v, uint8_t len)
{
    if (adress + len - 1 > EEPROM_MAX)
        return (1);
    for (uint8_t i = 0; i < len; i++)
    {
        if (eeprom_read(adress + i, &v[i]))
            return(len - i);
    }
    return (0);
}

void    display_line(uint16_t line)
{
    char line_str[9] = {0};
    line_str[8] = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        line_str[7-i] = HEXA[line % 16];
        line /= 16;
    }
    uart_printstr(line_str);
    uart_printstr(" ");
}

void    display_byte(uint8_t byte)
{
    uart_tx(HEXA[byte % 16]);
    uart_tx(HEXA[byte / 16]);
}

void    display_vector(uint8_t *v, uint8_t c)
{
    for (uint8_t i = 0; i < 16; i++)
    {
        display_byte(v[i]);
        if (i % 2 == 1)
            uart_printstr(" ");
          
    }
    if (c)
    {
        uart_printstr("  |");
        for(uint8_t i = 0; i < 16; i++)
        {
            if (is_print(v[i]))
                uart_tx((char)v[i]);
            else if (v[i] == FREE_BCK){
                uart_printstr(BLUE_PRINT);
                uart_tx('#');
                uart_printstr(BLACK_PRINT);
            }
            else if (v[i] == MEMO_BCK){
                uart_printstr(BLUE_PRINT);
                uart_tx('$');
                uart_printstr(BLACK_PRINT);
            }
            else
                uart_tx('.');
        }
        uart_tx('|');
    }
    uart_printstr("\r\n");
}


void    eeprom_hexdump(uint8_t c)
{
    uint16_t line = 0;
    uint16_t adress = 0;
    uint8_t v[16] = {0};
    uint8_t prev[16] = {0};
    uint8_t same = 0;
    while(adress + 0x9 <= EEPROM_MAX)
    {
        if (eeprom_read_vector(adress, v, 0x10))
        {
            uart_printstr("error while reading\r\n");
            break;
        }
        if (ft_memcmp(v, prev, 16) || adress == 0 || adress == 0x3f0){
            display_line(line);
            display_vector(v, c);
            ft_memcpy(prev, v, 16);
            same = 0;
        }
        else{
            if (same == 0)
            {    
                uart_printstr("  ...  \r\n");
                same = 1;
            }
        }

        line += 0x10;
        adress += 0x10;
        _delay_ms(50);
    }
    // display_line(line);
    // uint8_t byte;
    // while(adress <= EEPROM_MAX)
    // {
    //     _delay_ms(10);
    //     if (eeprom_read(adress, &byte))
    //     {
    //         uart_printstr("error while reading\r\n");
    //         break;
    //     }
    //     display_byte(byte);
    //     if (adress % 2 == 1)
    //         uart_printstr(" ");
    //     adress++;
    // }
}

void    display_vector_highlight(uint8_t *v, uint8_t red_idx)
{
    for (uint8_t i = 0; i < 16; i++)
    {
        if (i == red_idx)
            uart_printstr(RED_PRINT);
        display_byte(v[i]);
        if (i == red_idx)
            uart_printstr(BLACK_PRINT);
        if (i % 2 == 1)
            uart_printstr(" ");
          
    }
    uart_printstr("\r\n");
}

void    eeprom_hexdump_highlight(uint16_t highlight)
{
    uint16_t line = 0;
    uint16_t adress = 0;
    uint8_t v[16] = {0};
    uint8_t prev[16] = {0};
    uint8_t same = 0;
    uint8_t red_idx = 0;
    uint8_t print = 0;
    while(adress + 0x10 <= EEPROM_MAX)
    {
        if (adress <= highlight && adress + 0x10 > highlight)
        {
            print = 1;
            red_idx = highlight - adress;
        }
        if (eeprom_read_vector(adress, v, 0x10))
        {
            uart_printstr("error while reading\r\n");
            break;
        }
        if (print)
        {
            display_line(line);
            display_vector_highlight(v, red_idx);
            ft_memcmp(prev,v, 16);
            same = 0;
            print = 0;
            red_idx = 0;
        }
        else if (ft_memcmp(v, prev, 16) || adress == 0){
            display_line(line);
            display_vector(v, 0);
            ft_memcpy(prev, v, 16);
            same = 0;
        }
        else{
            if (same == 0)
            {    
                uart_printstr("  ...  \r\n");
                same = 1;
            }
        }

        line += 0x10;
        adress += 0x10;
        _delay_ms(50);
    }
    display_line(line);
    uint8_t byte;
    while(adress <= EEPROM_MAX)
    {
        _delay_ms(10);
        if (eeprom_read(adress, &byte))
        {
            uart_printstr("error while reading\r\n");
            break;
        }
        display_byte(byte);
        if (adress % 2 == 1)
            uart_printstr(" ");
        adress++;
    }
}



/* 
{7f==occupied} keySize valueSize        key value header size = 3
{8f == free}   BlockSize BlockSize
Biggest occupied block 1 + 1 + 1 + 64 = 67
Min occupied block 1+1+1+1+1 = 5
{e1 == initialised}
*/
//update idx to the next block
uint8_t next_block(uint16_t *idx)
{
    uint8_t     byte;
    uint16_t    jump = 0;    
    if (eeprom_read(*idx, &byte))
        return (1);
    if (byte == FREE_BCK)
    {   
        if (eeprom_read_word(*idx+1, &jump))
            return(1);
        *idx += HEADER_SIZE + jump;
        return (0);

    }
    else if (byte == MEMO_BCK)
    {
        if (eeprom_read(*idx+1, &byte))
            return(1);
        jump += (uint16_t)byte;
        if (eeprom_read(*idx+2, &byte))
            return(1);
        jump += (uint16_t)byte;
        *idx += HEADER_SIZE + jump;
        return (0);
    }
    else{
        *idx += 1;
        return (next_block(idx));
    }
}

//advance to the next memo block with keysize
uint8_t find_memo_block(uint16_t *idx, uint8_t key_size)
{
    uint8_t     byte = 0;
    uint8_t     size = 0;
    while(*idx <= LAST_BLOCK )
    {   
        if (next_block(idx))
            return (1);
        if (eeprom_read(*idx, &byte))
            return (1);
        if (byte == MEMO_BCK)
        {
            if (eeprom_read(*idx+1, &size))
                return (1);
            if (size == key_size)
                return (0);
        }
    }
    return (1);
}

uint8_t find_free_block(uint16_t *idx, uint16_t size)
{
    uint8_t     byte = 0;
    uint16_t    available= 0;
    while(*idx <= LAST_BLOCK)
    { 
        if (eeprom_read(*idx, &byte))
        {
            return (1);
        }
        if (byte == FREE_BCK)
        {
            if (eeprom_read_word(*idx+1, &available))
            {
                return (1);
            }
            if (size <= available)
                return (0);
        }
        if (next_block(idx)){
            return (1);
        }
    }    
    return (1);
}


uint8_t     test_block_get(uint16_t idx, char *key)
{
    uint8_t     key_size = ft_strlen(key);
    uint8_t     value_size = 0;
    if (eeprom_read_vector(idx + 3, key_b, key_size))
            return(1);
    key_b[key_size] = 0;
    if (ft_strcmp(key_b, key) == 0)
    {
        eeprom_read(idx+2, &value_size);
        if (eeprom_read_vector(idx + 3 + key_size, value_b, value_size))
            return (1);
        value_b[value_size] = 0;
        return (0);
    }
    return(1);
}
uint8_t        eeprom_get(char *key, uint16_t *cursor)
{
    uint16_t    idx = MEMO_START;
    ft_memset(key_b, 33, 0);
    ft_memset(value_b, 81, 0);
    uint8_t     key_size = ft_strlen(key);
    uint8_t ret = 0;
    eeprom_read(idx, &ret);
    if (ret == MEMO_BCK && test_block_get(idx, key) == 0)
    {
            *cursor = idx;
            return (0);
    }
    while((ret = find_memo_block(&idx, key_size)) == 0)
    {
        if (test_block_get(idx, key) == 0)
        {
            *cursor = idx;
            return (0);
        }
    }
    return (1);
}
//idx is pointing to a big enough free block
uint8_t    split_free_block(uint16_t idx, uint8_t key_size, uint8_t value_size)
{
    uint16_t free_size = 0;
    uint16_t total = key_size + value_size;
    eeprom_read_word(idx+1, &free_size);
    if (free_size >= total + 5)
    {
        eeprom_write(idx, MEMO_BCK);
        eeprom_write(idx+1, key_size);
        eeprom_write(idx+2, value_size);
        eeprom_write(idx+3+total, FREE_BCK);
        eeprom_write_word(idx+3+total+1, free_size - total -3);
        return (value_size);
    }
    else{
        eeprom_write(idx, MEMO_BCK);
        eeprom_write(idx+1, key_size);
        eeprom_write(idx+1, (uint8_t)(free_size - key_size));
        return (free_size - key_size);  
    }
}

uint16_t    eeprom_insert(char *key, char *value)
{
    uint16_t    idx = MEMO_START;
    if (eeprom_get(key, &idx) == 0){
        return (ALREADY_EXIST);
    }
    uint8_t     value_size = 0; 
    uint16_t total_size = ft_strlen(key) + ft_strlen(value);
    if (find_free_block(&idx, total_size))
    {
        return (NO_SPACE_LEFT);
    }    
        
    value_size = split_free_block(idx, ft_strlen(key), ft_strlen(value));
    ft_memset(key_b, 33, 0);
    ft_memset(value_b, 81, 0);
    ft_memcpy(key_b, key, ft_strlen(key));
    ft_memcpy(value_b, value, ft_strlen(value));
    eeprom_write_vector(idx + 3, key_b, ft_strlen(key));
    eeprom_write_vector(idx+3+ft_strlen(key), value_b, value_size);
    return (idx);
}

void eeprom_mem_init(uint8_t force)
{
    const uint8_t first[4] = {0xa1, 0xb2, 0xc3, 0xd4};
    uint8_t read_first[4] = {0};
    eeprom_read_vector(0x00, read_first, 4);
    if (ft_memcmp(first, read_first, 4) == 0 && force == 0)
        return;
    else{
        
        eeprom_write_vector(0x00, first, 4);
        eeprom_write(MEMO_START, FREE_BCK);
        eeprom_write_word(MEMO_START+1, 0x03f9);
    }
}

static uint8_t  previous_block(uint16_t idx, uint16_t *prev)
{
    if (idx < MEMO_START)
        return (1);
    uint8_t byte = 0;
    *prev = idx-1;
    while(*prev >= MEMO_START)
    {
        if (eeprom_read(*prev, &byte))
            return (1);
        if (byte == FREE_BCK)
            return (0);
        else if (byte == MEMO_BCK)
            return (1);
        *prev -= 1;
    }
    return (1);
}

void eeprom_defrag(uint16_t idx, uint16_t size)
{
    uint16_t    next = idx + HEADER_SIZE + size;
    uint16_t    next_s = 0;
    uint8_t     byte = 0;
    if (!eeprom_read(next, &byte) && byte == FREE_BCK)
    {
        eeprom_read_word(next+1, &next_s);
        eeprom_write(next, 0);
        eeprom_write_word(idx+1, size+next_s+HEADER_SIZE);
        uart_str_code("merged with next block", next, 16);
    }
    if (previous_block(idx, &next) == 0)
    {
        uint16_t prev_s = 0;
        eeprom_read_word(next+1, &prev_s);
        eeprom_write(idx, 0);
        eeprom_write_word(next+1, size+next_s+HEADER_SIZE+prev_s);
        uart_str_code("merged with previous block", next, 16);
    }

}

uint8_t     eeprom_delete(char *key)
{
    uint16_t idx = 0;
    if (eeprom_get(key, &idx) != 0){
        return (NOT_FOUND);
    }
    
    uint8_t byte = 0;
    uint16_t  size = 0;
    eeprom_read(idx+1, &byte);
    size += byte;
    eeprom_read(idx+2, &byte);
    size += byte;
    eeprom_write(idx, FREE_BCK);
    eeprom_write_word(idx+1, size);
    eeprom_defrag(idx, size);
    return (0);

}



