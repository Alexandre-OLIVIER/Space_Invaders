/*
 * bunker.c
 *
 *  Created on: 8 févr. 2020
 *      Author: alexandre
 */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "vt100.h"
#include "serial.h"
#include "stdint.h"
#include "bunker.h"

typedef struct
{
	uint8_t xbk;
	uint8_t ybk;
} bunker;

uint8_t nbk = 0;
bunker bunkers[27];
char bunker_item = '=';
/*
bunker *bunker_ptr;
bunker_ptr = bunkers;



void init_bunker(void)
{

	//return ptr;
}

/*
uint8_t col_bunker(uint8_t *x, uint8_t y, uint8_t z, uint8_t a)
{
	uint8_t xm = x;
	uint8_t ym = y;
	uint8_t xv = z;
	uint8_t missile_lance = a;

 Gestion bunkers
	for (nbk = 0; nbk < 27; nbk++)
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
			ym = 21;
		}

 for (nbomb = 0; nbomb < 12; nbomb++)
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
	return xm;
}
 */

