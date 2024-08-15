#ifndef SKILLCOMPONENT_H
#define SKILLCOMPONENT_H

class SkillComponent
{
private:

public:
	class Skill
	{
	private:
		int level,
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
							
							this->expNext = pow(this->level, 2.75) + this->level * 9.5 + this->expNext * 1.5;
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

							this->expNext = pow(this->level, 2.75) + this->level * 9.5 + this->expNext * 1.5;
						}
					}
				}
			}
		}
		void setLevel(const int level) { this->level = level; }
		void setLevel(const int LevelCap) { this->LevelCap = LevelCap; }
		Skill()
		{
			this->InitComponents();
		}

		~Skill()
		{

		}
		void update()
		{
		}
	};
	SkillComponent();
	virtual ~SkillComponent();

};

#endif // !SKILLCOMPONENT_H

