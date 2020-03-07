#ifndef VARIABLES_H_
#define VARIABLES_H_
#include "stdint.h"
#define origine_ym (21)
#define nb_aliens (21)
#define nb_bombs (2)
#define nb_bunkers (18)


typedef struct
{
	uint8_t xa;
	uint8_t ya;
	uint8_t direction;
	uint8_t alive;
} struct_alien;

typedef struct
{
	uint8_t xb;
	uint8_t yb;
} struct_bomb;

typedef struct
{
	uint8_t xbk;
	uint8_t ybk;
} struct_bunker;



#endif /* VARIABLES_H_ */
