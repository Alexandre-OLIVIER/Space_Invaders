#include "vt100.h"
#include "serial.h"
#include "stdint.h"
#include "Menu_init.h"

uint8_t inp_clav;
uint8_t selection = 0;
char mode = 50;

void menu_init(uint8_t vie)
{
	vie = vie;
	vt100_move(37, 2);
	serial_puts("SPACE INVADERS");
	vt100_move(34, 4);
	serial_puts("by Alexandre OLIVIER");
	vt100_move(25, 10);
	serial_puts("Q = Left / M = Missile / D = Right");
	vt100_move(35, 14);
	serial_puts("-> Play <-");
	vt100_move(29, 17);
	serial_puts("   Select difficulty   ");
	vt100_move(30, 20);
	serial_puts("Press <SPACE> to start");

	while (inp_clav != 32) /*32 ASCII de l'espace*/
	{
		inp_clav = serial_get_last_char();

		if (inp_clav == 'z')
		{
			selection = 0;
			refresh_screen();
		}
		if (inp_clav == 's')
		{
			selection = 1;
			refresh_screen();
		}
	}
	if (selection == 1)
	{
		select_difficulty();
	}
	/*switch (selection)
	{
	case 0:

		break;
	case 1:
		select_difficulty();
		break;
	 }*/

	vt100_clear_screen();
	vt100_move(37, 2);
	serial_puts("SPACE INVADERS");
	vt100_move(2, 2);
	serial_puts("SCORE: ");
	vt100_move(10, 2);
	serial_puts("0");
	vt100_move(70, 2);
	serial_puts("VIES: ");
	vt100_move(75, 2);
	serial_putchar(vie);

}

void refresh_screen(void)
	{
		if (selection == 0)
		{
			vt100_move(35, 14);
			serial_puts("-> Play <-");
			vt100_move(29, 17);
			serial_puts("   Select difficulty   ");
		}
		if (selection == 1)
		{
			vt100_move(35, 14);
			serial_puts("   Play   ");
			vt100_move(29, 17);
			serial_puts("-> Select difficulty <-");
		}
	}


void select_difficulty(void)
{
	vt100_clear_screen();
	while (inp_clav != 13) /*13 ASCII de entrer*/
	{
		inp_clav = serial_get_last_char();

		vt100_move(32, 2);
		serial_puts("Select difficulty");

		vt100_move(35, 10);
		serial_puts(" 1  Easy   ");
		vt100_move(35, 13);
		serial_puts(" 2  Medium   ");
		vt100_move(35, 16);
		serial_puts(" 3  Hard   ");
		vt100_move(35, 20);
		serial_puts(" Press Enter to play   ");


		if (inp_clav == '1')
		{
			vt100_move(33, 5);
			serial_puts(" Selected Easy    ");
			mode = 49;
		}
		if (inp_clav == '2')
			{
			vt100_move(33, 5);
			serial_puts(" Selected Medium  ");
			mode = 50;
		}
		if (inp_clav == '3')
		{
			vt100_move(33, 5);
			serial_puts(" Selected Hard   ");
			mode = 51;
		}

	}
	vt100_clear_screen();
}
