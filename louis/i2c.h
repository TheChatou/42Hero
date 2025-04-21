#ifndef I2C_H
#define I2C_H

#include "emb.h"
#include <util/twi.h>

#ifndef I2C_FREQ
#define I2C_FREQ 100000
#endif

#ifndef I2C_PRESCALER
#define I2C_PRESCALER 1
#endif

#define I2C_DONE (TWCR & (1 << TWINT))

#ifndef SEND_LOG
#define SEND_LOG 0
#endif

void    i2c_init();
uint8_t i2c_start();
void    i2c_stop();
uint8_t i2c_slaw_init(uint8_t adress);
uint8_t i2c_slar_init(uint8_t adress);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read(uint8_t *date, uint8_t ack);

#endif