/******************************************************************************************************
 * Tile Map Editor
 * Copyright (C) 2009-2017 Brandon Whitehead (tricksterguy87[AT]gmail[DOT]com)
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * excluding commercial applications, and to alter it and redistribute it freely,
 * subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    An acknowledgement in your documentation and link to the original version is required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 ******************************************************************************************************/
#ifndef PIXEL_BASED_COLLISION_LAYER_HPP
#define PIXEL_BASED_COLLISION_LAYER_HPP

#include <vector>

#include "CollisionLayer.hpp"
#include "Rectangle.hpp"
#include "Region.hpp"

/** Collision layer that is pixel based.
  * Collision information is defined as a list of rectangles specifying where the player can't go.
  */
class PixelBasedCollisionLayer : public CollisionLayer
{
public:
    /** Creates a collision layer with a predefined set of collision rectangles. */
    PixelBasedCollisionLayer(const std::vector<Rectangle>& rectangles);
    /** Creates an empty collision layer that is pixel based */
    PixelBasedCollisionLayer();
    bool operator==(const PixelBasedCollisionLayer& other) const;
    bool operator!=(const PixelBasedCollisionLayer& other) const { return !(*this == other); }

    /** @see CollisionLayer::clear */
    virtual void Clear() { region.Clear(); }
    /** @see CollisionLayer::shift */
    virtual void Shift(int horizontal, int vertical, bool wrap = false);
    /** @see CollisionLayer::resize */
    virtual void Resize(uint32_t width, uint32_t height, bool copy = true);

    const Region& GetData() const { return region; }

    /** @see Region::Add */
    void Add(const Rectangle& rectangle) { region.Add(rectangle); }
    /** @see Region::Xor */
    void Xor(const Rectangle& rectangle) { region.Xor(rectangle); }
    /** @see Region::Subtract */
    void Subtract(const Rectangle& rectangle) { region.Subtract(rectangle); }
    /** @see Region::Intersect */
    void Intersect(const Rectangle& rectangle) { region.Intersect(rectangle); }

protected:
    /** Region backing the PixelBasedCollisionLayer */
    Region region;
};

#endif
