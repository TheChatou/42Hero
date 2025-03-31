# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gburtin <gburtin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 10:15:21 by gburtin           #+#    #+#              #
#    Updated: 2025/03/31 17:23:37 by gburtin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = main

SRC = main.c
BIN = $(NAME).bin
HEX = $(NAME).hex

OBJ = $(SRC:.c=.o)

CC = avr-gcc
# Flags: errors, header directory, code size optimisation, MPU
CFLAGS = -Wall -I. -Os -mmcu=atmega328p -DF_CPU=16000000

all: hex flash clean

#burn hex files into microcontroller
flash:
	avrdude -p m328p -c arduino -P /dev/ttyACM0 -b 115200 -U flash:w:$(HEX):i

#create hex files
hex: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(BIN) 
	avr-objcopy -O ihex $(BIN) $(HEX)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@  

clean:
	rm -f $(HEX)
	rm -f $(BIN)
	rm -f $(OBJ)

re: clean all

.PHONY : all clean re