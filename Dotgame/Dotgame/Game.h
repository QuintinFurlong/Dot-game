
#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "Dot.h"

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

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	Dot dot;

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

