#ifndef ATRIBUTECOMPONENT_H
#define ATRIBUTECOMPONENT_H
class AtributeComponent
{
private:

public:
	int level;
	int exp;
	int expnext;
	int atributePoints;

	int strength;
	int vitality;
	int dexterity;
	int agility;
	int intalligance;

	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accurity;
	int defence;
	int luck;
	AtributeComponent(int level);
	~AtributeComponent();
	string DebugPrint() const;
	void calculateExpNext();
	void gainExp(const int exp);
	void levelUp();
	void update();
	void UpdateStats(const bool reset);
	void UpdateLevel();
};

#endif