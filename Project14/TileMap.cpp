#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height,  const string& texture_file)
{
	this->GridSizeF = gridSize;
	this->GridsizeU = static_cast<unsigned>(this->GridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->Texture_file = texture_file;
	 
	this->T_map.resize(this->maxSize.x, vector<vector<Tile*>>());
	for (int x = 0; x < this->maxSize.x; x++)
	{
		for (int y = 0; y < this->maxSize.y; y++)
		{
			this->T_map[x].resize(this->maxSize.y, vector<Tile*>());
			for (int z = 0; z < this ->layers; z++)
			{
				this->T_map[x][y].resize(this->layers, NULL);
			}
		}
	}
	if (!this->tileSheet.loadFromFile(this->Texture_file))
		throw "ERROR";
}

TileMap::~TileMap()
{
	for (int x = 0; x < this->maxSize.x; x++)
	{

		for (int y = 0; y < this->maxSize.y; y++)
		{
			for (int z = 0; z < this->layers; z++)
			{
				delete this->T_map[x][y][z];
			}
		}
	}
}

const Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

void TileMap::AddTile(const unsigned x, const unsigned y, const unsigned z, const IntRect& tex_rect)
{
	if (x < this->maxSize.x && x >= 0
		&& y < this->maxSize.y && y >= 0
		&& z < this->layers && z >= 0)
	{
		if (this->T_map[x][y][z] == NULL)
		{
			this->T_map[x][y][z] = new Tile(x * this->GridSizeF,y * this->GridSizeF,this->GridSizeF, this->tileSheet,tex_rect);
		}
	}
}

void TileMap::RemoveTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSize.x && x >= 0
		&& y < this->maxSize.y && y >= 0
		&& z < this->layers && z >= 0)
	{
		if (this->T_map[x][y][z] != NULL)
		{
			delete this->T_map[x][y][z];
			this->T_map[x][y][z] = NULL;
		}
	}
}

void TileMap::saveToFile(const string file_name)
{
	/*Saves the entire tilemap to txt.file
	Format:
	Basic:
	Size x, y
	gridSizee
	layers
	texture_file

	All tiles:
	gridPos x y, Texture rect x, y
	*/
	ofstream out_file;

	out_file.open(file_name);

	if(out_file.is_open())
	{ 
		out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->GridsizeU << "\n"
			<< this->layers << "\n"
			<< this->Texture_file << "\n";
		for (int x = 0; x < this->maxSize.x; x++)
		{

			for (int y = 0; y < this->maxSize.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if(this->T_map[x][y][z])
						out_file << this->T_map[x][y][z]->getAsString() << " ";
				}
			}
		}
	}
	else
	{
		throw "Bad Token";
	}
	out_file.close();
}

void TileMap::loadToFile(const string file_name)
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
			for (auto* z : y)
			{
				if(z != NULL)
					z->render(target);
			}
		}
	}
}
