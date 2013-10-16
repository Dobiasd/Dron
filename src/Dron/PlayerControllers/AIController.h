/*
 * Dron (Dobi's Tron/Snake game)
 * Copyright (C) 2012 Tobias Hermann

 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DRON_AICONTROLLER_H_
#define DRON_AICONTROLLER_H_

#include "../PlayerController.h"

#include <random>
#include <memory>

namespace Dron
{

/*
 * An "Artificial intelligence" tron player
 * It just runs around, avoids walls, collects items if next to them,
 * and sometimes randomly changes its direction.
 */
class AIController: public PlayerController
{
public:
	AIController(const std::string& name, double randomness);
	virtual void PushKeyInput(const sf::Key::Code&) override
	{}
	virtual void CalculateNextDirection(const World& world, const Player& Player, ConstPlayerPtrs otherPlayerPtrs)
	override;
	typedef std::vector<Vector> Directions;
	typedef Vector2D<int> Vector;
protected:
	std::random_device randomDevice_;
	mutable std::mt19937 randomGenerator_;
	mutable std::uniform_real_distribution<> randomDoubleDistribution_;
	Directions possibleDirections_;
	double randomness_;
};

typedef std::shared_ptr<AIController> AIControllerPtr;
typedef std::shared_ptr<const AIController> ConstAIControllerPtr;

} /* namespace Dron */

#endif /* DRON_AICONTROLLER_H_ */
