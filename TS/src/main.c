#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "vt100.h"
#include "serial.h"
#include "stdint.h"

int main(void)
{
	/*Variables compteur*/
	int h = 0;
	int i = 0;
	int k = 0;
	int j = 0;
	/*Variables alien*/
	int va = 0;
	uint8_t xa[30] =
	{ 0 };
	uint8_t ya[30] =
	{ 0 };
	uint8_t sens[30] =
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1 };
	uint8_t alive[30] =
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1 };

	char b = 51;
	uint8_t vie = b;
	char a = 48;
	uint8_t score = a;

	uint8_t inp_clav;
	uint8_t xv = 40;
	uint8_t yv = 20;

	uint8_t missile_lance = 0;
	uint8_t xm = 40;
	uint8_t ym = 21;
	uint8_t xb = 0;
	uint8_t yb = 4;
	char ship = 'o';
	char missile = '^';
	char alien = '#';
	char bombs = '*';

	serial_init(115200);
	vt100_clear_screen();

	/* Menu*/
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

	/*Init alien*/
	for (va = 0; va < 10; va++)
	{
		ya[va] = 3;
		vt100_move(xa[va], ya[va]);
		serial_putchar(alien);
		xa[va] = va * 3;
	}
	for (va = 10; va < 20; va++)
	{
		ya[va] = 5;
		vt100_move(xa[va], ya[va]);
		serial_putchar(alien);
		xa[va] = (va - 10) * 3;
	}
	for (va = 20; va < 30; va++)
	{
		ya[va] = 7;
		vt100_move(xa[va], ya[va]);
		serial_putchar(alien);
		xa[va] = (va - 20) * 3;
	}

	while (vie != 48)
	{
		i++;
		k++;
		j++;
		vt100_move(37, 2);
		serial_puts("SPACE INVADERS");
		vt100_move(2, 2);
		serial_puts("SCORE: ");
		vt100_move(13, 2);
		serial_putchar(score);
		vt100_move(70, 2);
		serial_puts("VIES: ");
		vt100_move(75, 2);
		serial_putchar(vie);
		vt100_move(xv, 20);
		serial_putchar(ship);
		inp_clav = serial_get_last_char();

		if (inp_clav == 'm')
		{
			missile_lance = 1;
		}

		if (missile_lance == 1)
		{
			h++;
			if (ym != 3 && h == 20)
			{
				vt100_move(xm, ym);
				serial_putchar(' ');
				ym -= 1;
				vt100_move(xm, ym);
				serial_putchar(missile);
				h = 0;

				if (ym == 3)
				{
					vt100_move(xm, 3);
					serial_putchar(' ');
					ym = 21;
					xm = xv;
					missile_lance = 0;
				}
			}
		}

		/*--Deplacement joueur--*/
		if (inp_clav == 'd')
		{
			vt100_move(xv, yv);
			serial_putchar(' ');
			if (xv != 80)
			{
				xv += 1;
			}
			vt100_move(xv, yv);
			serial_putchar(ship);
			if (xm != 80 && missile_lance == 0)
			{
				xm += 1;
			}

		}
		if (inp_clav == 'q')
		{
			vt100_move(xv, yv);
			serial_putchar(' ');
			if (xv != 0)
			{
				xv -= 1;
			}
			vt100_move(xv, yv);
			serial_putchar(ship);
			if (xm != 0 && missile_lance == 0)
			{
				xm -= 1;
			}
		}

		/*--Déplacement alien--*/
		if (i == 50)
		{
			for (va = 0; va < 30; va++)
			{
				if (alive[va] == 1)
				{
					if (sens[va] == 1)
					{
						vt100_move(xa[va], ya[va]);
						serial_putchar(' ');
						xa[va] += 1;
						vt100_move(xa[va], ya[va]);
						serial_putchar(alien);
						if (xa[va] == 80)
						{
							vt100_move(xa[va], ya[va]);
							serial_putchar(' ');
							ya[va] += 1;
							sens[va] = 0;
						}
					}
					if (sens[va] == 0)
					{
						vt100_move(xa[va], ya[va]);
						serial_putchar(' ');
						xa[va] -= 1;
						vt100_move(xa[va], ya[va]);
						serial_putchar(alien);
						if (xa[va] == 0)
						{
							vt100_move(xa[va], ya[va]);
							serial_putchar(' ');
							ya[va] += 1;
							sens[va] = 1;
						}

					}
					if (ya[va] == 20)
					{
						vie = 48;
					}
					i = 0;
				}

			}

		}

		/*--Gestion bombes alien--
		 if (j == 30)
		 {
		 vt100_move(xb, yb);
		 serial_putchar(' ');
		 yb += 1;
		 vt100_move(xb, yb);
		 serial_putchar(bombs);

		 if (yb == 23)
		 {
		 vt100_move(xb, 23);
		 serial_putchar(' ');
		 xb = xa;
		 yb = ya;
		 }
		 j = 0;
		 }
		 */

		/*Gestion score*/
		for (va = 0; va < 30; va++)
		{
			if (xm == xa[va] && ym == ya[va])
			{
				score += 1;
				alive[va] = 0;
				vt100_move(xa[va], ya[va]);
				serial_putchar(' ');
				ym = 21;
				xm = xv;
				missile_lance = 0;
				xa[va] = 2;
				ya[va] = 23;
				vt100_move(xa[va], ya[va]);
				serial_putchar(alien);
				vt100_move(10, 1);
				serial_puts("Alien KO");
			}

		}

		/*-Gestion vie-
		 if (xb == xv && yb == yv)
		 {
		 vie = vie - 1;
		 xb = xa;
		 yb = ya;
		 }
		 /*Collision missile - bombe
		 if (xm == xb && ym == yb)
		 {
		 vt100_move(xm, ym);
		 serial_putchar(' ');
		 xm = xv;
		 ym = 21;
		 xb = xa;
		 yb = ya;
		 }*/
	}
	vt100_clear_screen();
	while (inp_clav != 32)
	{
		vt100_move(37, 2);
		serial_puts("SPACE INVADERS");
		vt100_move(2, 2);
		serial_puts("SCORE: ");
		vt100_move(13, 2);
		serial_putchar(score);
		vt100_move(40, 10);
		serial_puts("LOSE");
	}

}
/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
	/* TODO, implement your code here */
	return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
	/* TODO, implement your code here */
	return -1;
}
