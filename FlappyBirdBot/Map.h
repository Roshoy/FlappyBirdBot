#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include <queue>

class Map : public sf::Drawable, public sf::Transformable 
{
public:
	Map(const sf::Vector2f& windowSize, double obstacles = 5, double speed = 3.5);
	void Update();
	void Reset();
	std::vector<sf::FloatRect> GetObstacles(double x);
	const double Speed;
private:
	const double MinGapHeight;
	const double MaxGapHeight;
	void SetUpObstacles(double count);
	double GetRandomHeight() const;
	std::vector<Obstacle> _obstacles;
	sf::Vector2f _windowSize;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

