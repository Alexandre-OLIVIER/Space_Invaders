#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "vt100.h"
#include "serial.h"
#include "stdint.h"
//#include "bunker.h"
#include "Menu_init.h"

#define origine_ym (21)

/*Structure*/
typedef struct
{
	uint8_t xa;
	uint8_t ya;
	uint8_t direction;
	uint8_t alive;
} alien;

typedef struct
{
	uint8_t xb;
	uint8_t yb;
} bomb;

typedef struct
{
	uint8_t xbk;
	uint8_t ybk;
} bunker;

int main(void)
{
	/*Variables compteur*/
	int h = 0;
	int i = 0;
	int k = 0;
	int j = 0;

	/*Variables alien*/
	uint8_t va = 0;
	alien aliens[30] =
	{ 0 };

	/*Variables bombes*/
	uint8_t random = 0;
	uint8_t nbomb = 0;
	bomb bombs[10] =
	{ 0 };

	char b = 51;
	uint8_t vie = b;
	uint8_t score = 0;
	uint8_t statut_game = 1; //1 = en cours, 0 = perdu, 2 = gagné
	uint8_t inp_clav;
	uint8_t xv = 40;
	uint8_t yv = 20;

	/*Variables missiles*/
	uint8_t missile_lance = 0;
	uint8_t xm = 40;
	uint8_t ym = 21;
	char ship = 'o';
	char missile = '^';
	char alien = '#';
	char bomb = '*';

	/*Variables bunker*/
	uint8_t nbk = 0;
	bunker bunkers[27];
	char bunker_item = '=';

	int rand(void);

	serial_init(115200);
	vt100_clear_screen();

	menu_init(vie);

	/*Init alien*/
	for (va = 0; va < 10; va++)
	{
		aliens[va].ya = 4;
		aliens[va].xa = va * 3;
		aliens[va].alive = 1;
		aliens[va].direction = 1;
	}
	for (va = 10; va < 20; va++)
	{
		aliens[va].ya = 6;
		aliens[va].xa = (va - 10) * 3;
		aliens[va].alive = 1;
		aliens[va].direction = 1;
	}
	for (va = 20; va < 30; va++)
	{
		aliens[va].ya = 8;
		aliens[va].xa = (va - 20) * 3;
		aliens[va].alive = 1;
		aliens[va].direction = 1;
	}
	for (va = 0; va < 30; va++)
	{
		vt100_move(aliens[va].xa, aliens[va].ya);
		serial_putchar(alien);
	}
	/*Init bunker*/
	for (nbk = 0; nbk < 3; nbk++)
	{
		bunkers[nbk].ybk = 17;
		bunkers[nbk].xbk = nbk + 20;
	}
	for (nbk = 3; nbk < 6; nbk++)
	{
		bunkers[nbk].ybk = 18;
		bunkers[nbk].xbk = (nbk - 3) + 20;
	}

	/*Second bunker complet*/
	for (nbk = 6; nbk < 9; nbk++)
	{
		bunkers[nbk].ybk = 17;
		bunkers[nbk].xbk = nbk + 32;
	}
	for (nbk = 9; nbk < 12; nbk++)
	{
		bunkers[nbk].ybk = 18;
		bunkers[nbk].xbk = (nbk - 3) + 32;
	}
	/*Troisieme bunker complet*/
	for (nbk = 12; nbk < 15; nbk++)
	{
		bunkers[nbk].ybk = 17;
		bunkers[nbk].xbk = nbk + 42;
	}
	for (nbk = 15; nbk < 18; nbk++)
	{
		bunkers[nbk].ybk = 18;
		bunkers[nbk].xbk = (nbk - 3) + 42;
	}

	for (nbk = 0; nbk < 18; nbk++)
	{
		vt100_move(bunkers[nbk].xbk, bunkers[nbk].ybk);
		serial_putchar(bunker_item);
	}
	/*Init bunker*/
	//init_bunker();

	/*Partie en cours*/
	while (statut_game == 1)
	{
		i++;
		k++;
		j++;

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
			if (ym != 3 && h == 60)
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
					ym = origine_ym;
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

		/*-----Déplacement alien-----*/
		if (i == 100)
		{
			for (va = 0; va < 30; va++)
			{
				if (aliens[va].alive == 1)
				{
					vt100_move(aliens[va].xa, aliens[va].ya);
					serial_putchar(' ');

					if (aliens[va].direction == 1)
					{
						aliens[va].xa += 1;
						vt100_move(aliens[va].xa, aliens[va].ya);
						serial_putchar(alien);
						if (aliens[va].xa == 81)
						{
							vt100_move(aliens[va].xa, aliens[va].ya);
							serial_putchar(' ');
							aliens[va].ya += 1;
							aliens[va].direction = 0;
						}
					}
					if (aliens[va].direction == 0)
					{
						aliens[va].xa -= 1;
						vt100_move(aliens[va].xa, aliens[va].ya);
						serial_putchar(alien);
						if (aliens[va].xa == 0)
						{
							vt100_move(aliens[va].xa, aliens[va].ya);
							serial_putchar(' ');
							aliens[va].ya += 1;
							aliens[va].direction = 1;
						}
					}
					if (aliens[va].ya == 20)
					{
						statut_game = 0;
					}
					i = 0;
				}
			}
		}

		/*--Gestion bombes alien--*/
		if (j == 150)
		{
			for (nbomb = 0; nbomb < 10; nbomb++)
			{
				random = rand() % 30;
				if (aliens[random].alive == 1)
				{
					vt100_move(bombs[nbomb].xb, bombs[nbomb].yb);
					serial_putchar(' ');
					bombs[nbomb].yb += 1;
					vt100_move(bombs[nbomb].xb, bombs[nbomb].yb);
					serial_putchar(bomb);

					if (bombs[nbomb].yb == 23)
					{
						vt100_move(bombs[nbomb].xb, 23);
						serial_putchar(' ');
						bombs[nbomb].xb = aliens[random].xa;
						bombs[nbomb].yb = aliens[random].ya;

					}
					j = 0;
				}
			}
		}

		/*Gestion score*/
		for (va = 0; va < 30; va++)
		{
			if (xm == aliens[va].xa && ym == aliens[va].ya)
			{
				score += 1;
				aliens[va].alive = 0;
				vt100_move(aliens[va].xa, aliens[va].ya);
				serial_putchar(' ');
				ym = origine_ym;
				xm = xv;
				missile_lance = 0;
				aliens[va].xa = 0;
				aliens[va].ya = 24;
				vt100_move(10, 1);
				serial_puts("Alien KO");
				vt100_move(13, 2);
				serial_putchar(score);
			}
		}
		if (score == 30)
		{
			statut_game = 2;
		}
		/*Collision bunker missile-----------------------------------------------------------------*/
		for (nbk = 0; nbk < 18; nbk++)
		{
			if (bunkers[nbk].xbk == xm && bunkers[nbk].ybk == ym)
			{
				vt100_move(20, 22);
				serial_puts("OK");
				vt100_move(bunkers[nbk].xbk, bunkers[nbk].ybk);
				serial_putchar(' ');
				bunkers[nbk].xbk = 80;
				bunkers[nbk].ybk = 24;
				missile_lance = 0;
				vt100_move(xm, ym);
				serial_putchar(' ');
				xm = xv;
				ym = origine_ym;
			}
			for (nbomb = 0; nbomb < 10; nbomb++)
			{
				if (bunkers[nbk].xbk == bombs[nbomb].xb
						&& bunkers[nbk].ybk == bombs[nbomb].yb)
				{
					vt100_move(bunkers[nbk].xbk, bunkers[nbk].ybk);
					serial_putchar(' ');
					bunkers[nbk].xbk = 80;
					bunkers[nbk].ybk = 24;
					random = rand() % 30;
					if (aliens[random].alive == 1)
					{
						bombs[nbomb].xb = aliens[random].xa;
						bombs[nbomb].yb = aliens[random].ya;
					}
				}
			}
		}

		/*-Gestion vie-*/
		for (nbomb = 0; nbomb < 10; nbomb++)
		{
			random = rand() % 30;
			if (aliens[random].alive == 1)
			{
				if (bombs[nbomb].xb == xv && bombs[nbomb].yb == yv)
				{
					vie = vie - 1;
					vt100_move(75, 2);
					serial_putchar(vie);
					bombs[nbomb].xb = aliens[random].xa;
					bombs[nbomb].yb = aliens[random].ya;
					if (vie == 48)
					{
						statut_game = 0;
					}
				}
				/*Collision missile - bombe*/
				if (xm == bombs[nbomb].xb && ym == bombs[nbomb].yb)
				{
					missile_lance = 0;
					vt100_move(xm, ym);
					serial_putchar(' ');
					xm = xv;
					ym = origine_ym;
					bombs[nbomb].xb = aliens[random].xa;
					bombs[nbomb].yb = aliens[random].ya;
				}
			}
		}
	}
	vt100_clear_screen();
	while (statut_game == 0) /*Partie perdue*/
	{
		vt100_move(37, 2);
		serial_puts("SPACE INVADERS");
		vt100_move(2, 2);
		serial_puts("SCORE: ");
		vt100_move(40, 10);
		serial_puts("LOSE!");
	}
	while (statut_game == 2) /*Partie gagnée*/
	{
		vt100_move(37, 2);
		serial_puts("SPACE INVADERS");
		vt100_move(2, 2);
		serial_puts("SCORE: ");
		vt100_move(40, 10);
		serial_puts("WIN!");
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
