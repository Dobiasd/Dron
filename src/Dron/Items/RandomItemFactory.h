#ifndef DRON_RANDOMITEMFACTORY_H_
#define DRON_RANDOMITEMFACTORY_H_

#include "../Item.h"
#include "../Player.h"
#include "../../Singleton.h"

#include <memory>
#include <random>

namespace Dron
{

class World;

/*
 * Spits out one random item to a free place in the tron world.
 */
class RandomItemFactory: public Singleton<RandomItemFactory>
{
public:
	RandomItemFactory();

	typedef std::unique_ptr<Item> ItemPtr;
	ItemPtr Create(const World& world, ConstPlayerPtrs playerPtrs) const;
protected:
	std::random_device randomDevice_;
	mutable std::mt19937 randomGenerator_;
	mutable std::uniform_int_distribution<> randomIntDistributionType_;
};

} /* namespace Dron */

#endif /* DRON_RANDOMITEMFACTORY_H_ */
