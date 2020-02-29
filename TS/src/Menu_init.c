/*
 * Menu_init.c
 *
 *  Created on: 18 févr. 2020
 *      Author: alexandre
 */
#include "vt100.h"
#include "serial.h"
#include "stdint.h"

uint8_t inp_clav;

void menu_init(uint8_t vie)
{
	vie = vie;
	vt100_move(37, 2);
	serial_puts("SPACE INVADERS");
	vt100_move(34, 4);
	serial_puts("by Alexandre OLIVIER");
	vt100_move(20, 10);
	serial_puts("Q = Gauche / Espace = Missile / D = Droite");
	vt100_move(33, 20);
	serial_puts("Press <SPACE> to start");

	while (inp_clav != 32) /*32 ASCII de l'espace*/
	{
		inp_clav = serial_get_last_char();
	}

	vt100_clear_screen();
	vt100_move(37, 2);
	serial_puts("SPACE INVADERS");
	vt100_move(2, 2);
	serial_puts("SCORE: ");
	vt100_move(13, 2);
	serial_puts("000");
	vt100_move(70, 2);
	serial_puts("VIES: ");
	vt100_move(75, 2);
	serial_putchar(vie);

}
