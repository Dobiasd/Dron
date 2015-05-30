#ifndef DRON_PLAYER_H_
#define DRON_PLAYER_H_

#include "../Vector2D.h"

#include "PlayerController.h"
#include "Item.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <string>
#include <list>
#include <memory>
#include <vector>

namespace Dron
{

class Player;

typedef std::shared_ptr<Player> PlayerPtr;
typedef std::shared_ptr<const Player> ConstPlayerPtr;
typedef std::vector<PlayerPtr> PlayerPtrs;
typedef std::vector<ConstPlayerPtr> ConstPlayerPtrs;

/*
 * A player inside the tron world
 *
 * The first position in the list of elements marks the head.
 */
class Player
{
public:
	typedef Vector2D<int> Position;
	typedef Vector2D<int> Vector;
	typedef sf::Rect<int> Rect;
	typedef std::list<Position> Positions;

	Player(const std::string& name, const Position& initialPosition, const sf::Color& color,
			const PlayerControllerPtr& controllerPtr, ItemPtrs::size_type maxItems, Positions::size_type minLength = 8);

	// Forward keyboard inputs to controller.
	void PushKeyInput(const sf::Key::Code& keyCode);

	// Forward joypad inputs to controller.
	void PushJoyInput(const sf::Event::JoyMoveEvent& jobMoveEvent);

	// Let the controller tell us what to do next.
	void CalculateNextStep(const World& world, ConstPlayerPtrs otherPlayerPtrs);
	bool RemovePosition(const Position& pos, World& world);
	void ExecuteNextStep(const World& world);

	// returns true if item is collected, false if not
	bool HitItem(const Position& pos, ItemPtr itemPtr, World& world);
	void HitWall(const Position& pos, World& world);
	void HitSelf(const Position& pos, World& world);
	void HitOtherPlayer(const Position& pos, Player& other, World& world);

	// Reduze tail length every nth step
	void ShrinkTail(std::size_t n = 2);
	bool IsAlive() const
	{
		return alive_;
	}

	// Where will his head be in the next time step in a given workd?
	const Position NextPosition(const World& world) const;

	// The head's position.
	const Position& GetFrontPosition() const;
	const Position& GetBackPosition() const;
	const sf::Color& GetColor() const
	{
		return color_;
	}
	const Positions& GetPositions() const
	{
		return positions_;
	}
	void SetPositions(const Positions& positions)
	{
		positions_ = positions;
	}
	const ItemPtrs& GetItemPtrs() const
	{
		return itemPtrs_;
	}

	const PlayerControllerPtr GetControllerPtr() const
	{
		return controllerPtr_;
	}
	Vector GetLastDirection() const
	{
		return lastDirection_;
	}
	void ShrinkToMinLength();
	const std::string& GetName() const
	{
		return name_;
	}
protected:
	void Die(const Position& position, World& world);
	std::string name_;
	Positions positions_;
	sf::Color color_;
	PlayerControllerPtr controllerPtr_;
	Vector lastDirection_;
	bool alive_;
	ItemPtrs::size_type maxItems_;
	Positions::size_type minLength_;
	ItemPtrs itemPtrs_;
	int shrinkTailStepNum_;
};

} /* namespace Dron */

#endif /* DRON_PLAYER_H_ */
