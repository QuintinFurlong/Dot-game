#pragma once
#include <SFML/Graphics.hpp>
class Dot
{
public:
	static const int RADIUS = 20;
	static const int MAX_SPEED = 10;

	Dot();
	void setPos(sf::Vector2f t_pos);
	void move(sf::Event t_event);
	void update();
	void draw(sf::RenderWindow & t_window);

	void setAsLocal(bool t_isLocal);
	void setAsChaser(bool t_isChaser);
	bool checkCollision(sf::Vector2f t_pos);
	void checkBoundaries();
	sf::Vector2f getPos();
private:
	bool isLocalPlayer, isChaser, right, left, up, down;
	sf::CircleShape body;
	sf::Vector2f velocity;
};