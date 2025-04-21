#include "i2c.h"



void    i2c_init()
{
    TWBR = ((F_CPU / (2*I2C_FREQ)) - 8)/I2C_PRESCALER;

    TWCR = (1 << TWEN);
}

uint8_t i2c_start()
{
    TWCR = (1 << TWSTA) | (1 << TWINT) | (1 << TWEN);

    while (!I2C_DONE)
        ;
    if (SEND_LOG)
        uart_str_code("Start init", TW_STATUS, 16);
    return (TW_STATUS != TW_START && TW_STATUS != TW_REP_START);
}

void    i2c_stop()
{
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
}

uint8_t i2c_slaw_init(uint8_t adress)
{
    TWDR = (adress << 1) | TW_WRITE;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!I2C_DONE)
        ;
    if (SEND_LOG)
        uart_str_code("SLA+W init", TW_STATUS, 16);
    return (TW_STATUS != TW_MT_SLA_ACK);
}

uint8_t i2c_slar_init(uint8_t adress)
{
    TWDR = (adress << 1) | TW_READ;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!I2C_DONE)
        ;
    if (SEND_LOG)
        uart_str_code("SLA+R init", TW_STATUS, 16);
    return (TW_STATUS != TW_MR_SLA_ACK);
}


uint8_t i2c_write(uint8_t data)
{
    TWDR = data;
    TWCR =  TWCR = (1 << TWINT) | (1 << TWEN);
    while (!I2C_DONE)
        ;
    if (SEND_LOG)
        uart_str_code("WRITE", TW_STATUS, 16);
    return (TW_STATUS != TW_MT_DATA_ACK);
}

uint8_t i2c_read(uint8_t *data, uint8_t ack)
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    if (ack)
        TWCR |= (1 << TWEA);
    while(!I2C_DONE)
        ;
    *data = TWDR;
    if (SEND_LOG)
        uart_str_code("READ", TW_STATUS, 16);
    if (ack)
        return (TW_STATUS != TW_MR_DATA_ACK);
    return (TW_STATUS != TW_MR_DATA_NACK);
}