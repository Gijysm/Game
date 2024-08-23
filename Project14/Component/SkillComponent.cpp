#include "..//stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
{
	this->InitSkills();
}

SkillComponent::~SkillComponent()
{
}

void SkillComponent::InitSkills()
{
	this->skills.push_back(Skill(SKILLS::Health));
	this->skills.push_back(Skill(SKILLS::Melle));
	this->skills.push_back(Skill(SKILLS::Ranged));
	this->skills.push_back(Skill(SKILLS::Endurance));
	this->skills.push_back(Skill(SKILLS::Accuracy));
	this->skills.push_back(Skill(SKILLS::Defence));
	this->skills.push_back(Skill(SKILLS::Mining));
	this->skills.push_back(Skill(SKILLS::Woodcutting));
}

const void SkillComponent::gainExp(const int skill, const int exp)
{
	if (!this->skills.empty() || !(skill < 0) || !(skill >= this->skills.size()))
	{
		return this->skills[skill].gainExp(exp);
	}
	else
	{
		throw"ERROR::SKILLCOMPONENT::GETSKILLLEVEL::Skill not found \n" + to_string(skill) + "Skill dont have";
	}
}

const int SkillComponent::getSkillLevel(const int index) const
{
	if (!this->skills.empty() || !(index < 0) || !(index >= this->skills.size()))
	{
		return this->skills[index].getLevel();
	}
	else
	{
		throw"ERROR::SKILLCOMPONENT::GETSKILLLEVEL::Skill not found \n" + to_string(index) + "Skill dont have";
	}
}
