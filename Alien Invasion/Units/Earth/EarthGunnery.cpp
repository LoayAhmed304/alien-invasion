#include "EarthGunnery.h"
#include "../../Game/Game.h"

EarthGunnery::EarthGunnery(int p, int h, int c, Game* g) : Units(earthGunnery, p, h, c, g)
{
	id = eID;
}

bool EarthGunnery::attack()
{
	Units* enemy = nullptr;
	LinkedQueue<Units*> temp;
	int i = 0;
	while (i < getAttackCap() && (!game->isEmpty(alienMonster) || !game->isEmpty(alienDrone)))
	{
		if (game->getUnit(alienMonster, enemy, game->getMonsterIndex()))
		{
			if (!enemy->getTa())
			{
				enemy->setTa(game->getTimestep());
				enemy->setDf(enemy->getTa() - enemy->getTj());
			}
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}
		if (game->getUnit(alienDrone, enemy))
		{
			if (!enemy->getTa())
			{
				enemy->setTa(game->getTimestep());
				enemy->setDf(enemy->getTa() - enemy->getTj());
			}
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}
		if (game->getUnit(alienDrone, enemy))
		{
			if (!enemy->getTa())
			{
				enemy->setTa(game->getTimestep());
				enemy->setDf(enemy->getTa() - enemy->getTj());
			}
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}
	}
	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
		{
			enemy->setTd(game->getTimestep());
			enemy->setDd(enemy->getTd() - enemy->getTa());
			enemy->setDb(enemy->getDf() + enemy->getDd());
			game->updateFile(enemy);
			game->kill(enemy);
		}
		else
			game->addUnit(enemy);
	}
	return true;
}