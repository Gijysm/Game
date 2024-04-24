#include "stdafx.h"
#include "AtributeComponent.h"

AtributeComponent::AtributeComponent(int level)
{
	this->level = level;
	this->exp = 0;
	this->expnext = (50 / 3) * (pow(this->level, 3) -
		6 * pow(this->level, 2) +
		(this->level * 17) - 12);
	this->atributePoints = 2;

	this->vitality = 1;
	this->agility = 1;
	this->strength = 1;
	this->dexterity = 1;
	this->intalligance = 1;

	this->UpdateLevel();
	this->UpdateStats(true);
}
AtributeComponent::~AtributeComponent()
{
}

string AtributeComponent::DebugPrint() const
{
	stringstream ss;
	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->exp << "\n"
		<< "Exp next: " << this->expnext << "\n"
		"Attp: " << this->atributePoints << "\n";
	return ss.str();
}

void AtributeComponent::gainExp(const int exp)
{
	this->exp += exp;

	this->UpdateLevel();
}

void AtributeComponent::update()
{
	this->UpdateLevel();
}

void AtributeComponent::UpdateStats(const bool reset)
{
	this->hpMax = this->vitality * 9 + this->vitality + this->strength + this->intalligance / 5;
	this->damageMax = this->strength * 2 + this->strength/2 + this->intalligance / 5;
	this->damageMin = this->strength * 2 + this->strength / 4 + this->intalligance / 5;
	this->accurity = this->dexterity * 5 + this->dexterity / 2+this->intalligance / 5;
	this->defence = this->agility * 2 / this->agility / 4 + this->intalligance / 5;
	this->luck = this->intalligance * 2 + this->intalligance / 5;
	if(reset)
	{
		this->hp = this->hpMax;
	}
}

void AtributeComponent::UpdateLevel()
{
	while (this->exp >= this->expnext)
	{
		++this->level;
		this->exp -= this->expnext;
		this->expnext = (50 / 3) * (pow(this->level, 3) -
			6 * pow(this->level, 2) +
			(this->level * 17) - 12);
		++this->atributePoints;
	}
}
