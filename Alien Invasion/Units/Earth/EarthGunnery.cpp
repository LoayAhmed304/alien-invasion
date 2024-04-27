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
	bool attacked = false;
	int i = 0;

	if (game->getUnit(alienMonster, enemy, game->getMonsterIndex()))
	{
		attacked = true;
		cout << "EG " << getID() << " shots [";
		if (!enemy->getTa())
			enemy->setTa(game->getTimestep());
		enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
		temp.enqueue(enemy);
		++i;
	}
	else if (game->getUnit(alienDrone, enemy))
	{
		attacked = true;
		cout << "EG " << getID() << " shots [";
		if (!enemy->getTa())
			enemy->setTa(game->getTimestep());
		enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
		temp.enqueue(enemy);
		++i;
	}

	while (i < getAttackCap() && (!game->isEmpty(alienMonster) || !game->isEmpty(alienDrone)))
	{
		if (game->getUnit(alienDrone, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			cout << ", ";
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}
		if (game->getUnit(alienDrone, enemy))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			cout << ", ";
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}
		if (game->getUnit(alienMonster, enemy, game->getMonsterIndex()))
		{
			if (!enemy->getTa())
				enemy->setTa(game->getTimestep());
			cout << ", ";
			enemy->getAttacked(this->getPower() * this->getCurHealth() / 100);
			temp.enqueue(enemy);
			++i;
		}
	}

	while (temp.dequeue(enemy))
	{
		if (enemy->isDead())
			game->kill(enemy);
		else
			game->addUnit(enemy);
	}

	if (attacked)
	{
		cout << "]\n";
		return true;
	}
	return false;
}