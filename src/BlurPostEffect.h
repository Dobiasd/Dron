#ifndef DRON_BLURPOSTEFFECT_H_
#define DRON_BLURPOSTEFFECT_H_

#include <SFML/Graphics.hpp>

/*
 * A simple GLSL (fragment shader) post effect blurring everything on the screen.
 */
class BlurPostEffect
{
public:
	BlurPostEffect();
	void AdjustToWindowSize(const sf::RenderTarget& renderTarget) const;
	void Apply(sf::RenderTarget& renderTarget) const;
private:
	// The effects are mutable, because they carry information
	// about the size of the windows they will be applied to.
	// These should be mutable in the GLSL code an thus be altered
	// from outside even on constant instances of sf::PostFX.
	// But this is not possible and AdjustToWindowSize has to be used in
	// bool PlayView::Display(sf::RenderTarget& renderTarget) const
	// To prevent the unconstness of propagating too far, they are set mutable here.
	mutable sf::PostFX effectX_;
	mutable sf::PostFX effectY_;
	bool enabled_;
};

#endif /* DRON_BLURPOSTEFFECT_H_ */
