#ifndef	SAVER_UNIT_H
#define SAVER_UNIT_H
#include "../Unit.h"
class Game;

class SaverUnit : public Unit
{
public:
	SaverUnit(int p, int h, int c, Game* g);
	bool attack();
};
#endif