#include "init_alien.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "vt100.h"
#include "serial.h"
#include "stdint.h"

int va = 0;

void init_alien(struct_alien *ptralien)
{

	for (va = 0; va < nb_aliens / 3; va++)
	{
		ptralien[va].ya = 4;
		ptralien[va].xa = va * 3;
		ptralien[va].alive = 1;
		ptralien[va].direction = 1;
	}
	for (va = nb_aliens / 3; va < 2 * (nb_aliens / 3); va++)
	{
		ptralien[va].ya = 6;
		ptralien[va].xa = (va - nb_aliens / 3) * 3;
		ptralien[va].alive = 1;
		ptralien[va].direction = 1;
	}
	for (va = 2 * (nb_aliens / 3); va < nb_aliens; va++)
	{
		ptralien[va].ya = 8;
		ptralien[va].xa = (va - 2 * (nb_aliens / 3)) * 3;
		ptralien[va].alive = 1;
		ptralien[va].direction = 1;
	}


}
