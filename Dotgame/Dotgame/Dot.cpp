#include "Dot.h"

Dot::Dot()
{
	body.setRadius(RADIUS);
	body.setOrigin(RADIUS/2, RADIUS/2);
	velocity = sf::Vector2f(0, 0);
	right = false;
	left = false;
	up = false;
	down = false;
}

void Dot::setPos(sf::Vector2f t_pos)
{
	body.setPosition(t_pos);
}

void Dot::move(sf::Event t_event)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Up == t_event.key.code && velocity.y > -MAX_SPEED)
		{
			up = true;
		}
		if (sf::Keyboard::Down == t_event.key.code && velocity.y < MAX_SPEED)
		{
			down = true;
		}
		if (sf::Keyboard::Left == t_event.key.code && velocity.x > -MAX_SPEED)
		{
			left = true;
		}
		if (sf::Keyboard::Right == t_event.key.code && velocity.x < MAX_SPEED)
		{
			right = true;
		}
	}
	if (sf::Event::KeyReleased == t_event.type)
	{
		if (sf::Keyboard::Up == t_event.key.code && velocity.y > -MAX_SPEED)
		{
			up = false;
		}
		if (sf::Keyboard::Down == t_event.key.code && velocity.y < MAX_SPEED)
		{
			down = false;
		}
		if (sf::Keyboard::Left == t_event.key.code && velocity.x > -MAX_SPEED)
		{
			left = false;
		}
		if (sf::Keyboard::Right == t_event.key.code && velocity.x < MAX_SPEED)
		{
			right = false;
		}
	}

}

void Dot::update()
{
	if (up)
	{
		velocity.y--;
	}
	if (down)
	{
		velocity.y++;
	}
	if (left)
	{
		velocity.x--;
	}
	if (right)
	{
		velocity.x++;
	}
	body.move(velocity);
	velocity *= 0.9f;
	checkBoundaries();
}

void Dot::draw(sf::RenderWindow& t_window)
{
	t_window.draw(body);
}

void Dot::setAsLocal(bool t_isLocal)
{
	isLocalPlayer = t_isLocal;
}

void Dot::setAsChaser(bool t_isChaser)
{
	isChaser = t_isChaser;
}

bool Dot::checkCollision(sf::Vector2f t_pos)
{
	return false;
}

void Dot::checkBoundaries()
{
	if (body.getPosition().x > 1000)
	{
		body.move(-1000,0);
	}
	else if (body.getPosition().x < 0)
	{
		body.move(1000, 0);
	}
	if (body.getPosition().y > 1000)
	{
		body.move(0, -1000);
	}
	else if (body.getPosition().y < 0)
	{
		body.move(0, 1000);
	}
}

sf::Vector2f Dot::getPos()
{
	return body.getPosition();
}

void Dot::setColour(sf::Color t_colour)
{
	body.setFillColor(t_colour);
}

sf::Color Dot::getColour()
{
	return body.getFillColor();
}
