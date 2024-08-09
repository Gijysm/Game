#ifndef WEAPON_H
#define WEAPON_H
class Weapon
{
private:
	Sprite sprite;
	Texture texture;
	Vector2f position;
public:
	Weapon(Texture& texture, Vector2f Position);
	~Weapon();
	Sprite& getSprite() { return this->sprite; }
	void setPosition(const Vector2f& position);
	void setRotation(const float& rotation);
	const Vector2f& getPosition() const;
	void updatePosition(const float& dt, Vector2f Position);
	void render(RenderTarget& target, Shader* shader = NULL, Vector2f Pos = Vector2f());
};

#endif // !WEAPON_H