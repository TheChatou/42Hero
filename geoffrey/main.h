/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:48:30 by gburtin           #+#    #+#             */
/*   Updated: 2025/03/31 15:39:52 by gburtin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <avr/io.h>
# include <util/delay.h>
# include <util/twi.h>

# define SPEED 100000
# define PRESCALER 1
# define SLA 0x38

void	i2c_init(void);
void	i2c_start(void);
void	i2c_stop(void);
void	i2c_write(unsigned char data);
void	i2c_read(void);
char	*i2c_debug(uint8_t status_code);

#endif