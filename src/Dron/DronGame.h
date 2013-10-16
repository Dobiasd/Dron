#ifndef DRON_DRONGAME_H_
#define DRON_DRONGAME_H_

#include "../Singleton.h"
#include "../Game.h"

#include <vector>

namespace Dron
{

/*
 * Initializes the window and game specific sounds.
 */
class DronGame: public Game, public Singleton<DronGame>
{
public:
	DronGame();
	virtual std::string GetName()
	override;
	virtual void InitSounds()
	override;
	virtual bool SoundsInitialized() const
	{
		return soundsInitialized_;
	}
protected:
	virtual bool Init()
	override;
	bool soundsInitialized_;
};

} /* namespace Dron */

#endif /* DRON_DRONGAME_H_ */
