#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H

enum SKILLS{
	Health = 0,
	Melle,
	Ranged,
	Endurance,
	Accuracy,
	Defence,
	Mining,
	Woodcutting
};

class SkillComponent
{
private:
	class Skill
	{
	private:
		int Type,
			level,
			LevelCap,
			exp,
			expNext;
		void InitComponents()
		{
			this->level = 1;
			this->LevelCap = 99;
			this->exp = 0;
			this->expNext = 75;
		}
	public:
		inline const int& getType() const { return this->Type; }
		inline const int& getLevel() const { return this->level; }
		inline const int& getExp() const { return this->exp; }
		inline const int& getExpNext() const { return this->expNext; }

		void gainExp(const int exp) { this->exp += exp; this->UpdateLevel(); }
		void LoseExp(const int exp) { this->exp += exp; this->UpdateLevel(); }
		
		inline void UpdateLevel(const bool up = true) {
			if(up)
			{
				if (this->level < this->LevelCap)
				{
					while (this->exp >= this->expNext)
					{
						if (this->level < this->LevelCap)
						{
							this->level++;
							
							this->expNext = std::pow(this->level, 2.75) + this->level * 9.5 + this->expNext * 1.5;
						}
					}
				}
			}
			else
			{
				if (this->level > 0)
				{
					while (this->level < 0)
					{
						if (this->level > 0)
						{
							this->level--;

							this->expNext = std::pow(this->level, 2.75) + this->level * 9.5 + this->expNext * 1.5;
						}
					}
				}
			}
		}
		void setLevel(const int level) { this->level = level; }
		void setLevelCap(const int LevelCap) { this->LevelCap = LevelCap; }
		Skill(const int type)
		{
			this->Type = type;
			this->InitComponents();
		}

		~Skill()
		{

		}
		void update()
		{
		}
	};
	vector<Skill> skills;
public:

	SkillComponent();
	virtual ~SkillComponent();

	void InitSkills();

	const void gainExp(const int skill, const int exp);
	const int getSkillLevel(const int index) const;
};

#endif // !SKILLCOMPONENT_H

