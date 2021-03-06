#include "Tileset.hpp"

constexpr uint32_t Tileset::MIN_TILE_SIZE;
constexpr uint32_t Tileset::MAX_TILE_SIZE;

Tileset::Tileset(const std::string& _filename, uint32_t _tile_width, uint32_t _tile_height) : filename(_filename), tile_width(_tile_width), tile_height(_tile_height)
{
}

void Tileset::Add(const AnimatedTile& tile)
{
    animated_tiles.push_back(tile);
}

void Tileset::SetTileDimensions(uint32_t width, uint32_t height)
{
    tile_width = width;
    tile_height = height;
}

void Tileset::GetTileDimensions(uint32_t& width, uint32_t& height) const
{
    width = tile_width;
    height = tile_height;
}
