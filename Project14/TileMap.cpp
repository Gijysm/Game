#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (int x = 0; x < this->maxGridSize.x; x++)
	{

		for (int y = 0; y < this->maxGridSize.y; y++)
		{
			for (int z = 0; z < this->layers; z++)
			{
				delete this->T_map[x][y][z];
				this->T_map[x][y][z] = NULL;
			}
			this->T_map[x][y].clear();
		}
		this->T_map[x].clear();
	}
	this->T_map.clear();

	// cout << this->T_map.size() << "\n";
}

TileMap::TileMap(float gridSize, unsigned sizex, unsigned sizey, unsigned width, unsigned height,  const string& texture_file)
{
	this->GridSizeF = gridSize;
	this->GridsizeU = static_cast<unsigned>(this->GridSizeF);
	this->maxGridSize.x = width;
	this->maxGridSize.y = height;
	this->maxGridSize_T.x = sizex;
	this->maxGridSize_T.y = sizey;
	this->MaxSizeWorld.x = static_cast<float>(width) * gridSize;
	this->MaxSizeWorld.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->Texture_file = texture_file;
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;
	 
	this->T_map.resize(this->maxGridSize.x, vector<vector<Tile*>>());
	for (int x = 0; x < this->maxGridSize.x; x++)
	{
		for (int y = 0; y < this->maxGridSize.y; y++)
		{
			this->T_map[x].resize(this->maxGridSize.y, vector<Tile*>());
			for (int z = 0; z < this ->layers; z++)
			{
				this->T_map[x][y].resize(this->layers, NULL);
			}
		}
	}
	if (!this->tileSheet.loadFromFile(this->Texture_file))
		throw "ERROR";

	this->collisionbox.setSize(Vector2f(gridSize, gridSize));
	this->collisionbox.setFillColor(Color(255, 0, 0, 10));
	this->collisionbox.setOutlineThickness(1);
	this->collisionbox.setOutlineColor(Color::Red);
}

TileMap::~TileMap()
{
	this->clear();
}

const Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

void TileMap::AddTile(const unsigned x, const unsigned y,
	const unsigned z, const IntRect& tex_rect,
	const bool& collision, const short& type)
{
	if (x < this->maxGridSize.x && x >= 0
		&& y < this->maxGridSize.y && y >= 0
		&& z < this->layers && z >= 0)
	{
		if (this->T_map[x][y][z] == NULL)
		{
			this->T_map[x][y][z] = new Tile(x,y,this->GridSizeF, this->tileSheet,tex_rect, collision, type);
		}
	}
}

void TileMap::RemoveTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxGridSize.x && x >= 0
		&& y < this->maxGridSize.y && y >= 0
		&& z < this->layers && z >= 0)
	{
		if (this->T_map[x][y][z] != NULL)
		{
			delete this->T_map[x][y][z];
			this->T_map[x][y][z] = NULL;
		}
	}
}

void TileMap::updateCollision(Entity* entity)
{
	if (entity->getPosition().x < 0)
	{
		entity->SetPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->MaxSizeWorld.x)
	{
		entity->SetPosition(this->MaxSizeWorld.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0)
	{
		entity->SetPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > static_cast<float>(this->maxGridSize.y) * GridSizeF)
	{
		entity->SetPosition(entity->getPosition().x, this->MaxSizeWorld.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}
	this->layer = 0;
	this->fromX = entity->getGridPos(this->GridsizeU).x - 1;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX > this->MaxSizeWorld.x)
	{
		this->fromX = this->MaxSizeWorld.x;
	}
	this->toX = entity->getGridPos(this->GridsizeU).x + 3;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX > this->MaxSizeWorld.x)
	{
		this->toX = this->MaxSizeWorld.x;
	}
	this->fromY = entity->getGridPos(this->GridsizeU).y - 1;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY > this->MaxSizeWorld.y)
	{
		this->fromY = this->MaxSizeWorld.y;
	}
	this->toY = entity->getGridPos(this->GridsizeU).y + 3;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY > this->MaxSizeWorld.y)
	{
		this->toY = this->MaxSizeWorld.y;
	}
	//for (int x = fromX; x < this->toX; x++)
	//{
	//	for (int y = fromY; y < this->toY; y++)
	//	{
	//		if (this->T_map[x][y][layer]->getCollision() && this->T_map[x][y][layer]->intersects(entity->getGlobalBounds()))
	//		{

	//		}
	//	}
	//}
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
		out_file << this->maxGridSize_T.x << " " << this->maxGridSize_T.y << "\n" << this->maxGridSize.x << " " << this->maxGridSize.y << "\n"
			<< this->GridsizeU << "\n"
			<< this->layers << "\n"
			<< this->Texture_file << "\n";
		for (int x = 0; x < this->maxGridSize.x; x++)
		{

			for (int y = 0; y < this->maxGridSize.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if(this->T_map[x][y][z])
						out_file  << x << " " << y << " " << z << " " << this->T_map[x][y][z]->getAsString() << " ";
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

void TileMap::loadFromFile(const string file_name)
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
	ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		Vector2u size;
		Vector2u size_T;
		unsigned GridSize;
		unsigned layers;
		string file_name = "";
		unsigned x = 0, y = 0, z = 0;
		unsigned Trx = 0, Try = 0, Trz = 0;
		bool collision = false;
		short type = 0;
		in_file >>size_T.x >> size_T.y >> size.x >> size.y >> GridSize >> layers >> file_name;

		this->GridSizeF = static_cast<float>(GridSize);
		this->GridsizeU = GridSize;
		this->maxGridSize.x = size.x;
		this->maxGridSize.y = size.y;
		this->layers = layers;
		this->Texture_file = file_name;

		this->clear();
		this->T_map.resize(this->maxGridSize.x, vector<vector<Tile*>>());
		for (int x = 0; x < this->maxGridSize.x; x++)
		{
			for (int y = 0; y < this->maxGridSize.y; y++)
			{
				this->T_map[x].resize(this->maxGridSize.y, vector<Tile*>());
				for (int z = 0; z < this->layers; z++)
				{
					this->T_map[x][y].resize(this->layers, NULL);
				}
			}
		}
		if (!this->tileSheet.loadFromFile(this->Texture_file))
			throw "ERROR";
		while(in_file >> x >> y >> z >> Trx  >> Try >> collision >> type)
		{
			this->T_map[x][y][z] = new Tile(x, y, GridSizeF, tileSheet, IntRect(Trx, Try, this->maxGridSize_T.x, this->maxGridSize_T.y), collision, type);
		}
	}
	else
	{
		throw "Bad Token";
	}
	in_file.close();
}

void TileMap::update()
{
}

void TileMap::render(RenderTarget& target, Entity* entity)
{
	if(entity)
	{
		this->layer = 0;
		this->fromX = entity->getGridPos(this->GridsizeU).x - 5;
		if (this->fromX < 0)
		{
			this->fromX = 0;
		}
		else if (this->fromX > this->MaxSizeWorld.x)
		{
			this->fromX = this->MaxSizeWorld.x;
		}
		this->toX = entity->getGridPos(this->GridsizeU).x + 8;
		if (this->toX < 0)
		{
			this->toX = 0;
		}
		else if (this->toX > this->MaxSizeWorld.x)
		{
			this->toX = this->MaxSizeWorld.x;
		}
		this->fromY = entity->getGridPos(this->GridsizeU).y - 5;
		if (this->fromY < 0)
		{
			this->fromY = 0;
		}
		else if (this->fromY > this->MaxSizeWorld.y)
		{
			this->fromY = this->MaxSizeWorld.y;
		}
		this->toY = entity->getGridPos(this->GridsizeU).y + 8;
		if (this->toY < 0)
		{
			this->toY = 0;
		}
		else if (this->toY > this->MaxSizeWorld.y)
		{
			this->toY = this->MaxSizeWorld.y;
		}
		for (int x = fromX; x < this->toX; x++)
		{
			for (int y = fromY; y < this->toY; y++)
			{
				if (T_map[x][y][layer] != NULL)
				{
					this->T_map[x][y][layer]->render(target);
					if (this->T_map[x][y][layer]->getCollision())
					{
						this->collisionbox.setPosition(this->T_map[x][y][layer]->getPosition());
						target.draw(this->collisionbox);
					}
				}
			}
		}
	}
	else
	{
		for (auto& x : this->T_map)
		{
			for (auto& y : x)
			{
				for (auto* z : y)
				{
					if (z != NULL)
					{
						z->render(target);
						if (z->getCollision())
						{
							this->collisionbox.setPosition(z->getPosition());
							target.draw(this->collisionbox);
						}
					}
				}
			}
		}
	}
}
