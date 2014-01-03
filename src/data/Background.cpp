/******************************************************************************************************
 * Tile Map Editor
 * Copyright (C) 2009-2013 Brandon Whitehead (tricksterguy87[AT]gmail[DOT]com)
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

#include "Background.hpp"

Background::Background(const std::string& _name, const std::string& _filename, int _mode, float _x, float _y) :
name(_name), filename(_filename), mode(_mode), x(_x), y(_y)
{
}

Background::~Background()
{
}

/**
  * Gets the speed of the background
  */
void Background::getSpeed(float& x, float& y) const
{
    x = this->x;
    y = this->y;
}

/**
  * Sets the speed of the background
  */
void Background::setSpeed(float x, float y)
{
    this->x = x;
    this->y = y;
}