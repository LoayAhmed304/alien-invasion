#ifndef	SAVER_UNIT_H
#define SAVER_UNIT_H
#include "../Units.h"
class Game;

class SaverUnit : public Units
{
public:
	SaverUnit(int p, int h, int c, Game* g);
	bool attack();
};
#endif