#include "stdafx.h"
#include "TileMap.h"
#include <cassert>

void TileMap::clear()
{
	if (!this->T_map.empty())
	{
		for (int x = 0; x < this->MaxSizeWorldI.x; x++)
		{

			for (int y = 0; y < this->MaxSizeWorldI.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					for (int k = 0; k < this->T_map[x][y][z].size(); k++)
					{
						delete this->T_map[x][y][z][k];
						this->T_map[x][y][z][k] = NULL;
					}
					this->T_map[x][y][z].clear();
				}
				this->T_map[x][y].clear();
			}
			this->T_map[x].clear();
		}
		this->T_map.clear();
	}
		// cout << this->T_map.size() << "\n";

}

TileMap::TileMap(float gridSize, int sizex, int sizey, int width, int height, const string& texture_file)
{
	this->GridSizeF = gridSize;
	this->GridsizeU = static_cast<int>(this->GridSizeF);
	this->MaxSizeWorldI.x = width;
	this->MaxSizeWorldI.y = height;
	this->maxGridSize_T.x = sizex;
	this->maxGridSize_T.y = sizey;
	this->MaxSizeWorldF.x = (static_cast<float>(width) * gridSize);
	this->MaxSizeWorldF.y = (static_cast<float>(height) * gridSize);
	this->layers = 1;
	this->Texture_file = texture_file;
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;
	 
	this->T_map.resize(this->MaxSizeWorldI.x, vector<vector<vector<Tile*>>>());
	for (int x = 0; x < this->MaxSizeWorldI.x; x++)
	{
		for (int y = 0; y < this->MaxSizeWorldI.y; y++)
		{
			this->T_map[x].resize(this->MaxSizeWorldI.y, vector< vector<Tile*>>());
			for (int z = 0; z < this ->layers; z++)
			{
				this->T_map[x][y].resize(this->layers, vector<Tile*>());
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

TileMap::TileMap(const string& texture_file)
{
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;
	loadFromFile(texture_file);

	this->collisionbox.setSize(Vector2f(this->GridSizeF, this->GridSizeF));
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

const bool TileMap::TileIsEmpty(const int x, const int y, const int z) const
{
	if(x >= 0 && x < this->MaxSizeWorldI.x &&
		y >= 0 && y < this->MaxSizeWorldI.y &&
		z >= 0 && z < this->layers)
	{
			return this->T_map[x][y][z].empty(); 
	}
	return false;
}

const int TileMap::getStackSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < this->T_map.size())
	{
		if (y >= 0 && y < this->T_map[x].size())
		{
			if (layer >= 0 && layer < this->T_map[x][y].size())
			{
				return this->T_map[x][y][layer].size();
			}
		}
	}
	return -1;
}

void TileMap::AddTile(const int x, const int y,
	const int z, const IntRect& tex_rect,
	const bool& collision, const short& type)
{
	if (x < this->MaxSizeWorldI.x && x >= 0
		&& y < this->MaxSizeWorldI.y && y >= 0
		&& z < this->layers && z >= 0)
	{
			this->T_map[x][y][z].push_back(new Tile(x,y,this->GridSizeF, this->tileSheet,tex_rect, collision, type));
	}
}

void TileMap::RemoveTile(const int x, const int y, const int z)
{
	if (x < this->MaxSizeWorldI.x && x >= 0
		&& y < this->MaxSizeWorldI.y && y >= 0
		&& z < this->layers && z >= 0)
	{
		if (!this->T_map[x][y][z].empty())
		{
			delete this->T_map[x][y][z][this->T_map[x][y][z].size()-1];
			this->T_map[x][y][z].pop_back();
		}
	}
}

void TileMap::updateCollision(Entity* entity, const float& dt)
{
	if (entity->getPosition().x < 0)
	{
		entity->SetPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->MaxSizeWorldF.x)
	{
		entity->SetPosition(this->MaxSizeWorldF.x -entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0)
	{
		entity->SetPosition(entity->getPosition().x, 0);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->MaxSizeWorldF.y)
	{
		entity->SetPosition(entity->getPosition().x, this->MaxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	this->layer = 0;
	this->fromX = entity->getGridPos(this->GridSizeF).x - 14;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX >= this->MaxSizeWorldI.x)
	{
		this->fromX = this->MaxSizeWorldI.x;
	}
	this->toX = entity->getGridPos(this->GridSizeF).x + 15;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX >= this->MaxSizeWorldI.x)
	{
		this->toX = this->MaxSizeWorldI.x;
	}
	this->fromY = entity->getGridPos(this->GridSizeF).y - 8;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY >= this->MaxSizeWorldI.y)
	{
		this->fromY = this->MaxSizeWorldI.y;
	}
	this->toY = entity->getGridPos(this->GridSizeF).y + 8;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY >= this->MaxSizeWorldI.y)
	{
		this->toY = this->MaxSizeWorldI.y;
	}

	for (int x = fromX; x < this->toX; x++)
	{
		for (int y = fromY; y < this->toY; y++)
		{
			if (!this->T_map[x][y][layer].empty())
			{
				for (int k = 0; k < this->T_map[x][y][this->layer].size(); k++)
				{
					FloatRect playerBounds = entity->getGlobalBounds();
					FloatRect NextPosition = entity->GetNextPosition(dt);
					FloatRect wallBounds = this->T_map[x][y][layer][k]->getGlobalBounds();
					if (this->T_map[x][y][layer][k]->getCollision() && this->T_map[x][y][layer][k]->intersects(NextPosition))
					{

						if (playerBounds.top < wallBounds.top
							&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left)
						{
							entity->stopVelocityY();
							entity->SetPosition(playerBounds.left, wallBounds.top - playerBounds.height);
						}
						else if (playerBounds.top > wallBounds.top
							&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left)
						{
							entity->stopVelocityY();
							entity->SetPosition(playerBounds.left, wallBounds.top + wallBounds.height);
						}
						if (playerBounds.left < wallBounds.left
							&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
							&& playerBounds.top < (wallBounds.top + wallBounds.height)
							&& playerBounds.top + playerBounds.height > wallBounds.top)
						{
							entity->stopVelocityX();
							entity->SetPosition(wallBounds.left - playerBounds.width, playerBounds.top);
						}
						else if (playerBounds.left > wallBounds.left
							&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
							&& playerBounds.top < (wallBounds.top + wallBounds.height)
							&& playerBounds.top + playerBounds.height > wallBounds.top)
						{
							entity->stopVelocityX();
							entity->SetPosition(wallBounds.left + wallBounds.width, playerBounds.top);
						}
					}
				}
			}
		} 
	}
}

const Vector2i& TileMap::GetMaxSizeGrid() const
{
	return this->MaxSizeWorldI;
}

const Vector2f& TileMap::GetMaxSizeF() const
{
	return this->MaxSizeWorldF;
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
		out_file << this->maxGridSize_T.x << " " << this->maxGridSize_T.y << "\n" << this->MaxSizeWorldI.x << " " << this->MaxSizeWorldI.y << "\n"
			<<  this->GridsizeU << "\n"
			<< this->layers << "\n"
			<< this->Texture_file << "\n";
		for (int x = 0; x < this->MaxSizeWorldI.x; x++)
		{

			for (int y = 0; y < this->MaxSizeWorldI.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if(!this->T_map[x][y][z].empty())
					{
						for (int k = 0; k < this->T_map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " <<
								this->T_map[x][y][z][k]->getAsString() << " ";
						}

					}
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
		int GridSize;
		int layers;
		string file_name = "";
		int x = 0, y = 0, z = 0;
		int Trx = 0, Try = 0, Trz = 0;
		bool collision = false;
		short type = 0;
		in_file >> maxGridSize_T.x >> maxGridSize_T.y >> size.x >> size.y >> GridSize >> layers >> file_name;

		this->GridSizeF = static_cast<float>(GridSize);
		this->GridsizeU = GridSize;
		this->MaxSizeWorldI.x = size.x;
		this->MaxSizeWorldI.y = size.y;
		this->MaxSizeWorldF.x = static_cast<float>(size.x * GridSize);
		this->MaxSizeWorldF.y = static_cast<float>(size.y * GridSize);
		this->layers = layers;
		this->Texture_file = file_name;


		this->clear();
		this->T_map.resize(this->MaxSizeWorldI.x, vector<vector<vector<Tile*>>>());
		for (int x = 0; x < this->MaxSizeWorldI.x; x++)
		{
			for (int y = 0; y < this->MaxSizeWorldI.y; y++)
			{
				this->T_map[x].resize(this->MaxSizeWorldI.y, vector< vector<Tile*>>());
				for (int z = 0; z < this->layers; z++)
				{
					this->T_map[x][y].resize(this->layers, vector<Tile*>());
				}
			}
		}
		if (!this->tileSheet.loadFromFile(this->Texture_file))
			throw "ERROR";
		while(in_file >> x >> y >> z >> Trx  >> Try >> collision >> type)
		{

			this->T_map[x][y][z].push_back(new Tile(x, y, GridSizeF, tileSheet, IntRect(Trx, Try, maxGridSize_T.x, maxGridSize_T.y), collision, type));
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

void TileMap::renderDeferrent(RenderTarget& target, Shader* shader, const Vector2f PlayerPos)
{
	while (!this->deferredRenderStack.empty())
	{
		if (shader)
		this->deferredRenderStack.top()->render(target, shader, PlayerPos);
		else
			this->deferredRenderStack.top()->render(target);
		this->deferredRenderStack.pop();
	}
}

void TileMap::render(RenderTarget& target,const Vector2i& GridPosition,
	Shader* shader, const Vector2f PlayerPos, bool Visability)
{
	this->layer = 0;

		this->fromX = GridPosition.x - 14;
		if (this->fromX <= 0)
		{
			this->fromX = 0;
		}
		else if (this->fromX >= this->MaxSizeWorldI.x)
		{
			this->fromX = this->MaxSizeWorldI.x;
		}
		this->toX = GridPosition.x + 15;
		if (this->toX <= 0)
		{
			this->toX = 0;
		}
		else if (this->toX >= this->MaxSizeWorldI.x)
		{
			this->toX = this->MaxSizeWorldI.x;
		}
		this->fromY = GridPosition.y - 8;
		if (this->fromY <= 0)
		{
			this->fromY = 0;
		}
		else if (this->fromY >= this->MaxSizeWorldI.y)
		{
			this->fromY = this->MaxSizeWorldI.y;
		}
		this->toY = GridPosition.y + 9;
		if (this->toY <= 0)
		{
			this->toY = 0;
		}
		else if (this->toY >= this->MaxSizeWorldI.y)
		{
			this->toY = this->MaxSizeWorldI.y;
		}
		for (int x = fromX; x != this->toX; x++)
		{
			for (int y = fromY; y != this->toY; y++)
			{
				for (int k = 0; k < this->T_map[x][y][this->layer].size(); k++)
				{
					if (this->T_map[x][y][layer][k]->GetType() == TileTypes::DOODAD)
					{
						this->deferredRenderStack.push(this->T_map[x][y][layer][k]);
					}
					else
					{
						if(shader)
							this->T_map[x][y][layer][k]->render(target, shader, PlayerPos);
						else
							this->T_map[x][y][layer][k]->render(target);
					}
					if (this->T_map[x][y][layer][k]->getCollision())
					{
						this->collisionbox.setPosition(this->T_map[x][y][layer][k]->getPosition());
						if(Visability)
						{
							target.draw(this->collisionbox);
						}
					}
				}
			}
		}
}
