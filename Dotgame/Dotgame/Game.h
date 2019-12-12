
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Dot.h"
#include "ClientStuff/Client.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct not_digit {
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	sf::Vector2f getVector(std::string t_pos);
	int getIndex(std::string t_index);
	float getTime(std::string t_time);

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text cornerMes; // text used for message on screen

	Dot dot, dot2;
	Client myClient;
	std::string playerPos;
	bool m_exitGame, endGame; // control exiting game
	int index;
	float timer;
};

#endif // !GAME_HPP

