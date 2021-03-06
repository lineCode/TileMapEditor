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
#ifndef TILED_LAYER_DATA_HPP
#define TILED_LAYER_DATA_HPP

#include <cstdint>
#include <string>
#include <vector>

/** Backend data for layers
  */
class TiledLayerData
{
public:
    /** Creates a new layer with the specified width, height and data.
      * @param width non-zero width of the layer.
      * @param height non-zero height of the layer.
      * @param data data which should be width*height ints.
      */
    TiledLayerData(uint32_t width, uint32_t height, const std::vector<int32_t>& data);
    /** Creates a new layer with the specified width, height and data.
      * @param width non-zero width of the layer.
      * @param height non-zero height of the layer.
      * @param data data which should be width*height ints.
      */
    TiledLayerData(uint32_t width, uint32_t height, const int32_t* data);
    /** Creates a new layer with the specified width, and height.
      * @param name name of the layer.
      * @param width non-zero width of the layer.
      * @param height non-zero height of the layer.
      */
    TiledLayerData(uint32_t width = MIN_SIZE, uint32_t height = MIN_SIZE);
    virtual ~TiledLayerData() {}

    int32_t& operator[](const uint32_t index) { return data[index]; }
    const int32_t& operator[](const uint32_t index) const { return data[index]; }

    /** Clears the layer. */
    void Clear();
    /** Shifts the entire layer in any direction a certain number of tiles.
      * @param horizontal amount to move left or right (negative = left).
      * @param vertical amount to move up or down (negative = up).
      * @param wrap if true any rows/columns will wrap around.
      */
    void Shift(int horizontal, int vertical, bool wrap = false);
    /** Resizes the layer to fit the new dimensions.
      * @param newwidth the new width of the layer in tiles.
      * @param newheight the new height of the layer in tiles.
      * @param copy if true then don't destroy the layer in the process if false then clear out the layer.
      */
    void Resize(uint32_t width, uint32_t height, bool copy = true);

    uint32_t GetWidth() const { return width; }
    uint32_t GetHeight() const { return height; }
    const std::vector<int32_t>& GetData() const { return data; }
    std::vector<int32_t>& GetData() { return data; }
    int32_t At(uint32_t index) const { return data[index]; }
    int32_t At(uint32_t x, uint32_t y) const { return At(y * width + x); }

    void SetData(const std::vector<int32_t>& _data) { data = _data; }
    void Set(uint32_t index, int32_t value) { data[index] = value; }
    void Set(uint32_t x, uint32_t y, int32_t value) { Set(y * width + x, value);}

    /** Minimum Size for a Layer */
    static constexpr uint32_t MIN_SIZE = 4;
    /** Maximum Size for a Layer */
    static constexpr uint32_t MAX_SIZE = 1024;
    /** Null tile id */
    static constexpr uint32_t NULL_TILE = 0xFFFFFFFF;

protected:
    /** Dimensions of this layer */
    uint32_t width, height;
    /** Tile ids for each location in the layer */
    std::vector<int32_t> data;
};

#endif

