#ifndef WEAPON_H
#define WEAPON_H
class Weapon
{
protected:
	Sprite sprite;
	Texture texture;
	Vector2f position;
	int MinDamage,
		MaxDamage;
public:
	Weapon(Texture& texture, Vector2f Position);
	 ~Weapon();
	 Sprite& getSprite() {
		return this->sprite;
	}
	 void setPosition(const Vector2f& position);
	 void setRotation(const float& rotation);
	 const Vector2f& getPosition() const;
	 virtual void updatePosition(const float& dt, Vector2f Position) = 0;
	 virtual void render(RenderTarget& target, Shader* shader = NULL, Vector2f Pos = Vector2f())= 0;
};

#endif // !WEAPON_H