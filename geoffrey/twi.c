/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:17:53 by gburtin           #+#    #+#             */
/*   Updated: 2025/03/15 16:03:09 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void i2c_init(void)
{
	// Calculate bit rate: (F_CPU / TWI Clock - 16) / (2 * Prescaler)
	TWBR = (F_CPU / SPEED - 16) / (2 * PRESCALER) & 0xFF;

	// Enable TWI module
	TWCR = (1 << TWEN);
}

void i2c_start(void)
{
	// Send start condition
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	// Wait for TWINT Flag set. This indicates that the START condition has been transmitted
	while (!(TWCR & (1 << TWINT)));
}

void i2c_stop(void)
{
	// Send stop condition
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void i2c_write(unsigned char data)
{
	// Load data into TWDR register
	TWDR = data;

	// Clear TWINT bit in TWCR to start transmission of data
	TWCR = (1 << TWINT) | (1 << TWEN);

	// Wait for TWINT Flag set. This indicates that the data has been transmitted
	while (!(TWCR & (1 << TWINT)));
}

void i2c_read(void)
{
	// Clear TWINT bit in TWCR to start transmission of data
	TWCR = (1 << TWINT) | (1 << TWEN);

	// Wait for TWINT Flag set. This indicates that the data has been transmitted
	while (!(TWCR & (1 << TWINT)));
}

char *i2c_debug(uint8_t status_code)
{
    if (status_code == TW_START)
        return ("START acknowledge.");
    else if (status_code == TW_REP_START)
        return ("REPEATED START acknowledge.");
    else if (status_code == TW_MT_SLA_ACK)
        return ("Master Transmitter: Slave ACK");
    else if (status_code == TW_MT_SLA_NACK)
        return ("Master Transmitter : Slave NACK");
    else if (status_code == TW_MT_DATA_ACK)
        return ("Master Transmitter : Data ACK");
    else if (status_code == TW_MT_DATA_NACK)
        return ("Master Transmitter: Data NACK");
    else if (status_code == TW_MR_SLA_ACK)
        return ("Master Receiver : Slave ACK");
    else if (status_code == TW_MR_SLA_NACK)
        return ("Master Receiver : Slave NACK");
    else if (status_code == TW_MR_DATA_ACK)
        return ("Master Receiver : Data ACK");
    else if (status_code == TW_MR_DATA_NACK)
        return ("Master Receiver : Data NACK");
    else if (status_code == TW_MT_ARB_LOST || status_code == TW_MR_ARB_LOST)
        return ("Arbitration Lost");
    else if (status_code == TW_ST_SLA_ACK)
        return ("Slave Transmitter : Slave ACK");
    else if (status_code == TW_ST_ARB_LOST_SLA_ACK)
        return ("Arbitration Lost in SLA+R/W, Slave ACK");
    else if (status_code == TW_ST_DATA_ACK)
        return ("Slave Transmitter : Data ACK");
    else if (status_code == TW_ST_DATA_NACK)
        return ("Slave Transmitter : Data NACK");
    else if (status_code == TW_ST_LAST_DATA)
        return ("Slave Transmitter : Last Data");
    else if (status_code == TW_SR_SLA_ACK)
        return ("Slave Receiver : Slave ACK");
    else if (status_code == TW_SR_ARB_LOST_SLA_ACK)
        return ("Arbitration Lost in SLA+R/W, Slave ACK");
    else if (status_code == TW_SR_GCALL_ACK)
        return ("General Call : Slave ACK");
    else if (status_code == TW_SR_ARB_LOST_GCALL_ACK)
        return ("Arbitration Lost in General Call, Slave ACK");
    else if (status_code == TW_SR_DATA_ACK)
        return ("Slave Receiver : Data ACK");
    else if (status_code == TW_SR_DATA_NACK)
        return ("Slave Receiver : Data NACK");
    else if (status_code == TW_SR_GCALL_DATA_ACK)
        return ("General Call : Data ACK");
    else if (status_code == TW_SR_GCALL_DATA_NACK)
        return ("General Call : Data NACK");
    else if (status_code == TW_SR_STOP)
        return ("Slave Receiver : STOP received");
    else if (status_code == TW_NO_INFO)
        return ("No state information available");
    else if (status_code == TW_BUS_ERROR)
        return ("Bus Error");
    else
        return ("Unknown Status Code");
}
