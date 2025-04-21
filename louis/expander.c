#include "i2c.h"
#include "emb.h"


uint16_t    exp_read_ports()
{
    uint16_t    res;
    i2c_start();
    i2c_slaw_init(EXPANDER_ADRESS);
    i2c_write(EXPANDER_IP0);
    i2c_slar_init(EXPANDER_ADRESS);
    i2c_read((uint8_t *)&res, 1);
    i2c_read((uint8_t *)&res + 1, 0);
    i2c_stop();
    return (res);
}
uint8_t     exp_read_port(uint8_t p)
{
    uint8_t data = 0;
    i2c_start();
    i2c_slaw_init(EXPANDER_ADRESS);
    i2c_write(p);
    i2c_start();
    i2c_slar(EXPANDER_ADRESS);
    i2c_read(&data, 0);
    i2c_stop();
    return (data);

}

// set bit to 0 to set it as output 1 for input a bit counter intuitive
void    exp_conf_port(uint8_t port, uint8_t conf)
{
    i2c_start();
    i2c_slaw_init(EXPANDER_ADRESS);
    i2c_write(port);
    i2c_write(~conf);
    i2c_stop();
}

// set bit to 0 to set it as output 1 for input a bit counter intuitive
void    exp_conf_ports(uint8_t p0, uint8_t p1)
{
    i2c_start();
    i2c_slaw_init(EXPANDER_ADRESS);
    i2c_write(EXPANDER_CP0);
    i2c_write(~p0);
    i2c_write(~p1);
    i2c_stop();

}

//output high -> set to 0
void    exp_set_output(uint8_t port_id, uint8_t data)
{
    i2c_start();
    i2c_slaw_init(EXPANDER_ADRESS);
    i2c_write(port_id);
    i2c_write(data);
    i2c_stop();
}

void    exp_set_both_output(uint8_t p0, uint8_t p1)
{
    i2c_start();
    i2c_slaw_init(EXPANDER_ADRESS);
    i2c_write(EXPANDER_OP0);
    i2c_write(p0);
    i2c_write(p1);
    i2c_stop();
}