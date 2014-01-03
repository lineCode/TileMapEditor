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

#include "Layer.hpp"
#include <cstring>

Layer::Layer(const std::string& _name, uint32_t _width, uint32_t _height, const std::vector<int32_t>& _data) :
name(_name), width(_width), height(_height), data(_data)
{
}

Layer::Layer(const std::string& _name, uint32_t _width, uint32_t _height, const int32_t* _data) :
name(_name), width(_width), height(_height), data(_data, _data + width * height)
{
}

Layer::Layer(const std::string& _name, uint32_t _width, uint32_t _height) :
name(_name), width(_width), height(_height), data(width * height, -1)
{
}

Layer::Layer(const Layer& layer)
{
    name = layer.name;
    width = layer.width;
    height = layer.height;
    data = layer.data;
}

Layer::~Layer()
{
}

Layer& Layer::operator=(const Layer& layer)
{
    if (this != &layer)
    {
        name = layer.name;
        width = layer.width;
        height = layer.height;
        data = layer.data;
    }
    return *this;
}

bool Layer::operator==(const Layer& other)
{
    if (width != other.width && height != other.height)
        return false;
    if (name != other.name)
        return false;
    for (uint32_t i = 0; i < width * height; i++)
    {
        if (data[i] != other.data[i])
            return false;
    }

    return true;
}

void Layer::resize(uint32_t newwidth, uint32_t newheight, bool copy)
{
    if (newwidth == width && newheight == height) return;

    if (copy)
    {
        std::vector<int32_t> newdata = data;
        data.clear();
        data.reserve(width * height);

        uint32_t minw = newwidth > width ? width : newwidth;
        uint32_t minh = newheight > height ? height : newheight;
        int32_t excessx = (int32_t)(newwidth - width);
        int32_t excessy = (int32_t)(newheight - height);

        for (uint32_t i = 0; i < minh; i++)
        {
            data.insert(data.begin() + i * newwidth, newdata.begin() + i * width, newdata.begin() + i * width + minw);
            if (newwidth > width) data.insert(data.begin() + i * newwidth + width, -1, excessx);
        }

        if (newheight > height)
            data.insert(data.begin() + minh * newwidth, -1, newwidth * excessy);
    }
    else
    {
        data.assign(newwidth * newheight, -1);
    }

    width = newwidth;
    height = newheight;
}

void Layer::shift(int32_t horizontal, int32_t vertical, bool wrap)
{
/*    int32_t* newdata = new int32_t[width * height];

    if (!wrap)
        memset(newdata, 0xFF, sizeof(int32_t) * width * height);

    // TODO Make more efficient
    if (wrap)
    {
        for (uint32_t i = 0; i < height; i++)
        {
            for (uint32_t j = 0; j < width; j++)
            {
                int sx = (j - horizontal) % width;
                int sy = (i - vertical) % height;
                if (sx < 0) sx += width;
                if (sy < 0) sy += height;
                newdata[i * width + j] = data[sy * width + sx];
            }
        }
    }
    else
    {
        for (uint32_t i = 0; i < height; i++)
        {
            for (uint32_t j = 0; j < width; j++)
            {
                if (i - vertical < 0 || i - vertical >= height || j - horizontal < 0 || j - horizontal >= width) continue;
                newdata[i * width + j] = data[(i - vertical) * width + (j - horizontal)];
            }
        }
    }

    memcpy(data, newdata, sizeof(int32_t) * width * height);

    delete[] newdata;
    */
}

void Layer::clear()
{
    data.assign(width * height, -1);
}