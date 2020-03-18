#include "init_bunker.h"
#include "init_alien.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "vt100.h"
#include "serial.h"
#include "stdint.h"
#include "variables.h"
#include "Menu_init.h"
#include <stdio.h>

int main(void)
{
	/*Variables compteur*/
	int h = 0;
	int i = 0;
	int k = 0;
	int j = 0;

	/*Variables alien*/
	uint8_t va = 0;
	uint8_t vitesse_alien = 150;
	struct_alien aliens[nb_aliens] =
	{ 0 };
	struct_alien *ptralien = aliens;
	init_alien(ptralien);

	/*Variables bombes*/
	uint8_t random = 0;
	uint8_t nbomb = 0;
	uint8_t vitesse_bomb = 200;
	struct_bomb bombs[nb_bombs] =
	{ 0 };

	char b = 51;
	uint8_t vie = b;
	uint8_t score = 1;
	uint8_t statut_game = 1; //1 = en cours, 0 = perdu, 2 = gagné
	uint8_t inp_clav;
	uint8_t xv = 40;
	const uint8_t yv = 20;

	/*Variables missiles*/
	uint8_t missile_lance = 0;
	uint8_t xm = 40;
	uint8_t ym = 21;

	/*Variables bunker*/
	uint8_t nbk = 0;
	struct_bunker bunkers[nb_bunkers];
	struct_bunker *ptrbk = bunkers;
	init_bunker(ptrbk);

	char ship = 'o';
	char missile = '^';
	char alien_item = '#';
	char bomb_item = '*';
	char bunker_item = '=';

	char display_score[2];

	int rand(void);

	serial_init(115200);
	vt100_clear_screen();

	menu_init(vie);

	for (va = 0; va < nb_aliens; va++)
	{
		vt100_move(ptralien[va].xa, ptralien[va].ya);
		serial_putchar(alien_item);
	}

	for (nbk = 0; nbk < nb_bunkers; nbk++)
	{
		vt100_move(ptrbk[nbk].xbk, ptrbk[nbk].ybk);
		serial_putchar(bunker_item);
	}

	for (nbomb = 0; nbomb < nb_bombs; nbomb++)
	{
		random = rand() % nb_aliens;
		bombs[nbomb].xb = ptralien[random].xa;
		bombs[nbomb].yb = ptralien[random].ya;
	}
	extern char mode;

	/*Partie en cours*/
	while (statut_game == 1)
	{
		i++;
		k++;
		j++;

		sprintf(display_score, "%d", score);

		if (mode ==49)
		{
			vitesse_alien = 200;
			vitesse_bomb = 250;
		}
		if (mode == 50)
		{
			vitesse_alien = 150;
			vitesse_bomb = 200;
		}
		if (mode == 51)
		{
			vitesse_alien = 100;
			vitesse_bomb = 150;
		}

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
			if (ym != 3 && h == 80)
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
		if (i == vitesse_alien)
		{
			for (va = 0; va < nb_aliens; va++)
			{
				if (ptralien[va].alive == 1)
				{
					vt100_move(ptralien[va].xa, ptralien[va].ya);
					serial_putchar(' ');

					if (ptralien[va].direction == 1)
					{
						ptralien[va].xa += 1;
						if (ptralien[va].xa == 81)
						{
							ptralien[va].ya += 1;
							ptralien[va].direction = 0;
						}
					}
					if (ptralien[va].direction == 0)
					{
						ptralien[va].xa -= 1;
						if (ptralien[va].xa == 0)
						{
							ptralien[va].ya += 1;
							ptralien[va].direction = 1;
						}
					}
					vt100_move(ptralien[va].xa, ptralien[va].ya);
					serial_putchar(alien_item);

					if (ptralien[va].ya == 20)
					{
						statut_game = 0;
					}
					i = 0;
				}
			}
		}

		/*--Gestion bombes alien--*/
		if (j == vitesse_bomb)
		{
			for (nbomb = 0; nbomb < nb_bombs; nbomb++)
			{
				vt100_move(bombs[nbomb].xb, bombs[nbomb].yb);
				serial_putchar(' ');
				bombs[nbomb].yb += 1;
				vt100_move(bombs[nbomb].xb, bombs[nbomb].yb);
				serial_putchar(bomb_item);

				if (bombs[nbomb].yb == 23)
				{
					vt100_move(bombs[nbomb].xb, 23);
					serial_putchar(' ');
					random = rand() % nb_aliens;
					while (ptralien[random].alive == 0)
					{
						random = rand() % nb_aliens;
					}
					bombs[nbomb].xb = ptralien[random].xa;
					bombs[nbomb].yb = ptralien[random].ya;
				}
				j = 0;
			}
		}

		/*Gestion score*/
		for (va = 0; va < nb_aliens; va++)
		{
			if (xm == ptralien[va].xa && ym == ptralien[va].ya)
			{
				score += 1;
				ptralien[va].alive = 0;
				vt100_move(ptralien[va].xa, ptralien[va].ya);
				serial_putchar(' ');
				ym = origine_ym;
				xm = xv;
				missile_lance = 0;
				ptralien[va].xa = 0;
				ptralien[va].ya = 24;
				//vt100_move(10, 1);
				//serial_puts("Alien KO");
				vt100_move(10, 2);
				serial_puts(display_score);
			}
		}
		if (score == nb_aliens)
		{
			statut_game = 2;
		}
		/*Collision bunker missile*/
		for (nbk = 0; nbk < nb_bunkers; nbk++)
		{
			if (ptrbk[nbk].xbk == xm && ptrbk[nbk].ybk == ym)
			{
				vt100_move(ptrbk[nbk].xbk, ptrbk[nbk].ybk);
				serial_putchar(' ');
				ptrbk[nbk].xbk = 80;
				ptrbk[nbk].ybk = 24;
				missile_lance = 0;
				vt100_move(xm, ym);
				serial_putchar(' ');
				xm = xv;
				ym = origine_ym;
			}
			for (nbomb = 0; nbomb < nb_bombs; nbomb++)
			{
				if (ptrbk[nbk].xbk == bombs[nbomb].xb
						&& ptrbk[nbk].ybk == bombs[nbomb].yb)
				{
					vt100_move(ptrbk[nbk].xbk, ptrbk[nbk].ybk);
					serial_putchar(' ');
					ptrbk[nbk].xbk = 80;
					ptrbk[nbk].ybk = 24;
					random = rand() % nb_aliens;
					if (ptralien[random].alive == 1)
					{
						bombs[nbomb].xb = ptralien[random].xa;
						bombs[nbomb].yb = ptralien[random].ya;
					}
				}
			}
		}

		/*-Gestion vie-*/
		for (nbomb = 0; nbomb < nb_bombs; nbomb++)
		{
			random = rand() % nb_aliens;
			if (ptralien[random].alive == 1)
			{
				if (bombs[nbomb].xb == xv && bombs[nbomb].yb == yv)
				{
					vie = vie - 1;
					vt100_move(75, 2);
					serial_putchar(vie);
					bombs[nbomb].xb = ptralien[random].xa;
					bombs[nbomb].yb = ptralien[random].ya;
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
					bombs[nbomb].xb = ptralien[random].xa;
					bombs[nbomb].yb = ptralien[random].ya;
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
		vt100_move(10, 2);
		serial_puts(display_score);
		vt100_move(40, 10);
		serial_puts("LOSE!");
	}
	while (statut_game == 2) /*Partie gagnée*/
	{
		vt100_move(37, 2);
		serial_puts("SPACE INVADERS");
		vt100_move(2, 2);
		serial_puts("SCORE: ");
		vt100_move(10, 2);
		serial_puts(display_score);
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
