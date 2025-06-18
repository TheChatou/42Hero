NAME = main.hex

FREQ = 16000000UL

CC = avr-gcc

ARCH = atmega2560

CFLAGS = -mmcu=$(ARCH) -I$(INC_DIR) -DF_CPU=$(FREQ) -O2 -Wall -Wextra -MMD -MP

SRCS_FILES = main.c

BUILD_DIR = .objs/
SRCS_DIR = ./
INC_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS = $(addprefix $(BUILD_DIR), $(SRCS_FILES:.c=.o))

ELF_NAME = $(addprefix $(BUILD_DIR), $(NAME:.hex=.elf))

DEP = $(OBJS:.o=.d)

all: hex flash

-include $(DEP)


$(BUILD_DIR)%.o: $(SRCS_DIR)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF_NAME): $(OBJS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(NAME) : $(ELF_NAME)
	avr-objcopy -j .text -j .data -O ihex $< $@


hex : $(NAME)

uart: hex flash
	screen /dev/ttyACM0 115200

#port ?? https://avrdudes.github.io/avrdude/8.0/avrdude.pdf
flash: $(NAME)
	avrdude -v -cwiring -b115200 -pm2560 -P /dev/ttyACM0 -D -U flash:w:$<:i

clean:
	rm -rf $(NAME) $(ELF_NAME) $(BUILD_DIR)