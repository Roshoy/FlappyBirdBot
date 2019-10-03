#include "Player.h"
#include <iostream>

double Player::Gravity = 0.25;
double Player::MaxSpeed = 7.5;

Player::Player(double size, const sf::Vector2f & position) :
	StartingPosition(position), _speed(0)
{
	_body.setSize(sf::Vector2f(size, size));
	_body.setPosition(position);
	_body.setFillColor(sf::Color::Yellow);
}

void Player::Update()
{
	_body.move(0, std::max((float)_speed, -_body.getPosition().y));
	if(_body.getPosition().y <= 0)
	{
		_speed = 0;
		_body.setPosition(sf::Vector2f(_body.getPosition().x, 1));
	}
	else
	{
		_speed += Gravity;
	}
}

void Player::Jump()
{
	_speed = -MaxSpeed;
}

void Player::Reset()
{
	_body.setPosition(StartingPosition);
	_speed = 0;
}

sf::Rect<float> Player::GetRect() const
{
	return _body.getGlobalBounds();
}

void Player::SetPosition(const sf::Vector2f & position)
{
	_body.setPosition(position);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Transform transform = getTransform();
	target.draw(_body, transform);
}
