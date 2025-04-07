# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chatou <chatou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 10:43:44 by fcoullou          #+#    #+#              #
#    Updated: 2025/04/05 15:07:03 by chatou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
## GENERAL CONFIG
################################################################################
#	Microcontrôleur cible.
MCU				= atmega328p
#	Fréquence du microcontrôleur en Hz.
F_CPU			= 16000000
#	ihex : Format de fichier hexadécimal Intel.
FORMAT 			= ihex
#	BAUD : Vitesse de transmission en bauds (bits par seconde).
BAUD_RATE		= 115200
#	PORT : Port série sur lequel le programmateur est connecté. (cmd : "ls /dev/ttyUSB*")
PORT			= /dev/ttyUSB0

################################################################################
##	FILES & DIRECTORIES
################################################################################
SRC       		= main.c uart.c
OBJDIR    		= objdep
OBJ				= $(SRC:%.c=$(OBJDIR)/%.o)
DEP      		= $(OBJ:.o=.d)

################################################################################
##	COMPILATION & FLAGS
################################################################################
CC 				= avr-gcc
##	CDEF : Définit les symboles dans tous les fichiers source.
#	-DF_CPU=$(F_CPU)UL : Définit le symbole F_CPU dans tous les fichiers source
CDEFS 			= -DF_CPU=$(F_CPU)UL
#	-DBAUD_RATE=$(BAUD_RATE) : Définit le symbole BAUD_RATE dans tous les fichiers source.
CDEFS		    += -DBAUD_RATE=$(BAUD_RATE)
#	-std=gnu99 : Utilise la norme C99 avec des extensions GNU.
 CDEFS 			+= -std=gnu99

##	CFLAGS : Options de compilation.
#	-Wall : Active tous les avertissements (-Wall).
#	-Werror : Traite les avertissements comme des erreurs (-Werror).
#	-Wextra : Active des avertissements supplémentaires (-Wextra).
 CFLAGS			= -Wall -Werror -Wextra
#	-I : Ajoute un répertoire au chemin de recherche des fichiers d'en-tête.
 CFLAGS 			+= -I./include
#	-g3 : Génère des informations de débogage détaillées dans le fichier exécutable.
# CFLAGS 			+= -g3
CFLAGS 			+= $(CDEFS)
#	-Os : Optimise pour la taille du code.
 CFLAGS 			+= -Os

##	CPPFLAGS : Options de préprocesseur.
#	-MMD : Génère des fichiers .d avec des dépendances pour chaque fichier source,
# utile pour la recompilation conditionnelle avec make.
CPPFLAGS		= -MMD
#	-c : Compile les fichiers source sans les lier, générant des fichiers objet (.o).
CPPFLAGS		+= -c

################################################################################
##	TOOLS
################################################################################
OBJCOPY 		= avr-objcopy
AVRDUDE 		= avrdude
REMOVE 			= rm -f
REMOVEDIR 		= rm -rf
MKDIR			= mkdir -p

################################################################################
##	RULES
################################################################################
all: hex flash

#	La règle hex compile les fichiers objets et génère le fichier hexadécimal.
# Mieux vaut séparer compilation (.o) et édition de liens.
hex: $(OBJ)
	$(CC) $(CFLAGS) -mmcu=$(MCU) -o main.bin $(OBJ)
	$(OBJCOPY) -O $(FORMAT) main.bin main.hex

$(OBJDIR):
	$(MKDIR) $@
	
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -mmcu=$(MCU) -o $@ $<

#	-c : Compile les fichiers source sans les lier, générant des fichiers objet (.o).
#	-p $(MCU) : Spécifie le microcontrôleur à programmer.
#	-b $(BAUD) : Spécifie la vitesse de transmission en bauds.
#	-U flash:w:$(SRC).hex : Écrit le fichier hexadécimal dans la mémoire flash du microcontrôleur.
flash:
	$(AVRDUDE) -c arduino -p $(MCU) -P $(PORT) -b $(BAUD_RATE) -U flash:w:main.hex

screen: all
	screen $(PORT) $(BAUD_RATE)

clean:
	$(REMOVE) main.bin main.hex $(OBJ) $(DEP)
	$(REMOVEDIR) $(OBJDIR)

################################################################################
##	PHONY TARGETS
################################################################################
.PHONY: all hex flash clean screen

################################################################################
##	DEPENDENCIES
################################################################################
-include $(DEP)