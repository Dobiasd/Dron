#ifndef DRON_ANIMATION_H_
#define DRON_ANIMATION_H_

#include <memory>
#include <list>

namespace sf
{
class RenderTarget;
}

namespace Dron
{

class World;

/*
 * Abstract base class for an animation
 * that can be placed somewhere inside the Dron world.
 */
class Animation
{
public:
	Animation() :
			isDone_(false)
	{
	}
	~Animation()
	{
	}

	// Calculate valued for the next frame
	virtual void Update(float elapsedTime) = 0;

	// Show in a window depending on the settings of the displayed world.
	virtual void Display(sf::RenderTarget& renderTarget, const World& world) const = 0;

	// Is the animation over and can be removed from the world?
	bool IsDone()
	{
		return isDone_;
	}

protected:
	void SetDone()
	{
		isDone_ = true;
	}
	bool isDone_;
};

typedef std::shared_ptr<Animation> AnimationPtr;
typedef std::shared_ptr<const Animation> ConstAnimationPtr;
typedef std::list<AnimationPtr> AnimationPtrs;
typedef std::list<ConstAnimationPtr> ConstAnimationPtrs;

} /* namespace Dron */
#endif /* DRON_ANIMATION_H_ */
