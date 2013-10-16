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
