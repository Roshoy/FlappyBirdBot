#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable, public sf::Transformable
{
public:
	Player(double size, const sf::Vector2f & position = sf::Vector2f(0,0));
	void Update();
	void Jump();
	void Reset();
	sf::FloatRect GetRect() const;
	void SetPosition(const sf::Vector2f & position);
private:
	const sf::Vector2f StartingPosition;
	static double Gravity;
	static double MaxSpeed;
	sf::RectangleShape _body;
	double _speed;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

