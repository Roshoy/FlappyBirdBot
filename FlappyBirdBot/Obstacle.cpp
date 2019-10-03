#include "Obstacle.h"
#include <iostream>


Obstacle::Obstacle(bool upper, const sf::Vector2f & position, const sf::Vector2f & size) :
	_upper(upper)
{
	_body.setSize(size);
	if(upper)
	{
		_body.setOrigin(_body.getOrigin().x, _body.getOrigin().y + _body.getSize().y);
	}
	_body.setPosition(position);
	if (_upper)
	{
		NewHeight(size.y / 10, _body.getPosition().y - size.y / 10);
	}
	else
	{
		NewHeight(_body.getPosition().y + size.y / 10, size.y * 9 / 10);
	}
	_body.setFillColor(sf::Color::White);
}

void Obstacle::UpdatePosition(double offset)
{
	_body.move(-offset, 0);
}

int Obstacle::NewHeight(double minHeight, double maxHeight)
{
	double newPosition = rand() % std::max(int(maxHeight - minHeight),1) + (_upper ? minHeight : _body.getSize().y - maxHeight);
	newPosition = _upper ? newPosition : _body.getSize().y - newPosition;
	_body.setPosition(_body.getPosition().x, newPosition);
	return newPosition;
}

double Obstacle::GetBoundary() const
{
	return _body.getGlobalBounds().top - GetObstacleVerticalOffset();
}

bool Obstacle::OutOfBounds() const
{
	return GetHorizontalPosition() + _body.getGlobalBounds().width < 0;
}

bool Obstacle::operator<(const Obstacle & other) const
{
	return GetHorizontalPosition() < other.GetHorizontalPosition() ||
		(GetHorizontalPosition() == other.GetHorizontalPosition() && _upper && !other._upper);
}

sf::FloatRect Obstacle::GetRect() const
{
	return _body.getGlobalBounds();
}

void Obstacle::SetColor(sf::Color color)
{
	_body.setFillColor(color);
}

double Obstacle::GetObstacleVerticalOffset() const
{
	return  _upper ? -_body.getGlobalBounds().height : 0;
}

double Obstacle::GetHorizontalPosition() const
{
	return _body.getGlobalBounds().left;
}

void Obstacle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//std::cout << GetHorizontalPosition() << " " << GetBoundary() << " | ";
	sf::Transform transform = getTransform();
	target.draw(_body, transform);	
}
