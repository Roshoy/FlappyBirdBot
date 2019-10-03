#pragma once
#include <SFML/Graphics.hpp>

class Obstacle: public sf::Drawable, public sf::Transformable
{
public:
	Obstacle(bool upper, const sf::Vector2f & position, const sf::Vector2f & size = sf::Vector2f(20.f,1000.f));
	void UpdatePosition(double offset);
	int NewHeight(double minHeight, double maxHeight);
	double GetBoundary() const;
	bool OutOfBounds() const;
	bool operator<(const Obstacle & other) const;
	sf::FloatRect GetRect() const;
	void SetColor(sf::Color color);
private:
	sf::RectangleShape _body;
	bool _upper;
	double GetObstacleVerticalOffset() const;
	double GetHorizontalPosition() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

