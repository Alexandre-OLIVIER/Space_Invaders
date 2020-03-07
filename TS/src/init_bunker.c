#include <init_bunker.h>
#include "stdint.h"

uint8_t nbk = 0;

void init_bunker(struct_bunker *ptrbk)
{

	/*Init bunker*/
	for (nbk = 0; nbk < 3; nbk++)
	{
		ptrbk[nbk].ybk = 17;
		ptrbk[nbk].xbk = nbk + 20;
	}
	for (nbk = 3; nbk < 6; nbk++)
	{
		ptrbk[nbk].ybk = 18;
		ptrbk[nbk].xbk = (nbk - 3) + 20;
	}

	/*Second bunker complet*/
	for (nbk = 6; nbk < 9; nbk++)
	{
		ptrbk[nbk].ybk = 17;
		ptrbk[nbk].xbk = nbk + 32;
	}
	for (nbk = 9; nbk < 12; nbk++)
	{
		ptrbk[nbk].ybk = 18;
		ptrbk[nbk].xbk = (nbk - 3) + 32;
	}
	/*Troisieme bunker complet*/
	for (nbk = 12; nbk < 15; nbk++)
	{
		ptrbk[nbk].ybk = 17;
		ptrbk[nbk].xbk = nbk + 42;
	}
	for (nbk = 15; nbk < 18; nbk++)
	{
		ptrbk[nbk].ybk = 18;
		ptrbk[nbk].xbk = (nbk - 3) + 42;
	}
}

