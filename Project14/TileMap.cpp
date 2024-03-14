#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	this->GridSizeF = gridSize;
	this->GridsizeU = static_cast<unsigned>(this->GridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	 
	this->T_map.resize(this->maxSize.x);
	for (int x = 0; x < this->maxSize.x; x++)
	{
		this->T_map.push_back(vector<vector<Tile>>());
		for (int y = 0; y < this->maxSize.y; y++)
		{
			this->T_map[x].resize(this->maxSize.y);
			this->T_map[x].push_back(vector<Tile>());
			for (int z = 0; z < this->layers; z++)
			{
				this->T_map[x][y].resize(this->layers);
				this->T_map[x][y].push_back(Tile(x * this->GridSizeF, y * this->GridSizeF, this->GridSizeF));
			}
		}
	}
}

TileMap::~TileMap()
{
}

void TileMap::update()
{
}

void TileMap::render(RenderTarget& target)
{
	for (auto& x : this->T_map)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.render(target);
			}
		}
	}
}
