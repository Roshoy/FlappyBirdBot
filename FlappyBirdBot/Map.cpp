#include "Map.h"
#include <iostream>


Map::Map(const sf::Vector2f& windowSize, double obstacles, double speed) :
	 Speed(speed), MinGapHeight(windowSize.y/4), MaxGapHeight(windowSize.y / 2), _windowSize(windowSize)
{
	SetUpObstacles(obstacles);
}

void Map::Update()
{
	bool changedOrdination = false;
	int lastNewPosition = -1;
	
	for(auto & obstacle : _obstacles)
	{
		obstacle.UpdatePosition(Speed);
		if(obstacle.OutOfBounds())
		{
			obstacle.UpdatePosition(-_windowSize.x);
			if (lastNewPosition < 0) {
				lastNewPosition = obstacle.NewHeight(_windowSize.y / 10, _windowSize.y * 9 / 10 - MinGapHeight);				
			}else
			{
				obstacle.NewHeight(lastNewPosition + MinGapHeight, std::min(lastNewPosition + MaxGapHeight , _windowSize.y * 9.0 / 10));
				lastNewPosition = -1;
			}
			changedOrdination = true;
		}
	}

	if(changedOrdination)
	{
		std::sort(_obstacles.begin(), _obstacles.end());
	}
}

void Map::Reset()
{
	const int count = _obstacles.size() / 2;
	_obstacles.clear();
	SetUpObstacles(count);
}

std::vector<sf::FloatRect> Map::GetObstacles(double x)
{
	std::vector<sf::FloatRect> result;
	for (auto& obstacle : _obstacles)
	{
		if(result.size() < 2 && obstacle.GetRect().left + obstacle.GetRect().width > x)
		{
			result.emplace_back(obstacle.GetRect());
			obstacle.SetColor(sf::Color::Red);
		}else
		{
			obstacle.SetColor(sf::Color::White);
		}
	}
	
	return result;
}

void Map::SetUpObstacles(double count)
{
	auto setUpObstacle = [this, count](bool upper, int i, double axis)
	{
		_obstacles.emplace_back(Obstacle(
			upper, sf::Vector2f(_windowSize.x / 4.f + int(_windowSize.x * (i + 1) / count), axis +
				(upper ? -1 : 1 ) * MinGapHeight / 2),sf::Vector2f(20, _windowSize.y)));
	};

	for (int i = 0; i<count; i++)
	{
		double axis = GetRandomHeight();
		setUpObstacle(true, i, axis);
		setUpObstacle(false, i, axis);
	}
	std::sort(_obstacles.begin(), _obstacles.end());
}


double Map::GetRandomHeight() const
{
	return rand() % int(_windowSize.y / 2) + _windowSize.y/4;
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Transform transform = getTransform();
	for (const auto & obstacle : _obstacles)
	{
		target.draw(obstacle, transform);		
	}
}
