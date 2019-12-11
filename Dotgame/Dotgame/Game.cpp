
#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 1000U, 32U }, "Dot Game" },
	m_exitGame{false}, //when true game will exit
	myClient("149.153.106.148", 1111)
{
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
	}
	setupFontAndText(); // load font 
	dot.setPos(sf::Vector2f(400, 400));
	dot2.setPos(sf::Vector2f(600, 600));
	dot.setColour(sf::Color::Blue);
	dot2.setColour(sf::Color::Red);
	index = 0;
	timer = 0;
	endGame = false;
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		dot.move(newEvent);
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	sf::Vector2f temp = getVector(playerPos);
	if (temp.x != int(dot.getPos().x) || temp.y != int(dot.getPos().y) || endGame)
	{
		playerPos = std::to_string(int(dot.getPos().x)) + " , " + std::to_string(int(dot.getPos().y));
		if(!endGame)
			playerPos += ", index: " + std::to_string(index) + ", " + std::to_string(timer);
		else
			playerPos += ", index: " + std::to_string(2) + std::to_string(timer);
		myClient.SendString(playerPos);
	}
	
	if (myClient.isMessage)
	{
		sf::Vector2f temp = getVector(myClient.newMessage);
		int tempIndex = getIndex(myClient.newMessage);
		if (temp.x != -10)
		{
			dot2.setPos(temp);
			if ((!(temp.x == dot.getPos().x && temp.y == dot.getPos().y)) && tempIndex == 0)
			{
				index = 1;
				dot.setColour(sf::Color::Red);
				dot2.setColour(sf::Color::Blue);
			}
			else if ((!(temp.x == dot.getPos().x && temp.y == dot.getPos().y)) && tempIndex == 1)
			{
				index = 0;
				dot.setColour(sf::Color::Blue);
				dot2.setColour(sf::Color::Red);
			}
			if (index == 0)
			{
				timer = getTime(myClient.newMessage);
			}
			if (tempIndex == 2)
			{
				endGame = true;
				m_welcomeMessage.setString("GAMEOVER \nTime lasted : " + std::to_string(int(timer)) + " seconds.");
			}
		}
		myClient.isMessage = false;
	}

	if (!endGame)
	{
		std::cout << index << std::endl;
		if (index == 0)
			m_welcomeMessage.setString("RUN");
		else if (index == 1)
			m_welcomeMessage.setString("CATCH");
		dot.update();
		if (index == 1)
		{
			timer += t_deltaTime.asSeconds();
			if (sqrt(pow(dot.getPos().x - dot2.getPos().x, 2) + pow(dot.getPos().y - dot2.getPos().y, 2)) < dot.RADIUS * 2)
			{
				m_welcomeMessage.setString("GAMEOVER \nTime lasted : " + std::to_string(int(timer)) + " seconds.");
				endGame = true;
			}
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear();
	dot.draw(m_window);
	dot2.draw(m_window);
	m_window.draw(m_welcomeMessage);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setFillColor(sf::Color::White);

}

sf::Vector2f Game::getVector(std::string t_pos)
{
	not_digit notADigit;
	string::iterator end = std::remove_if(t_pos.begin(), t_pos.end(), notADigit);
	string all_numbers(t_pos.begin(), end);

	stringstream ss(all_numbers);
	vector<int> vec;
	int i;
	for (; ss >> i;)
	{
		vec.push_back(i);
	}
	if (vec.size() < 2)
	{
		return sf::Vector2f(-10,-10);
	}
	return sf::Vector2f(vec.at(0), vec.at(1));
}

int Game::getIndex(std::string t_index)
{
	not_digit notADigit;
	string::iterator end = std::remove_if(t_index.begin(), t_index.end(), notADigit);
	string all_numbers(t_index.begin(), end);

	stringstream ss(all_numbers);
	vector<int> vec;
	int i;
	for (; ss >> i;)
	{
		vec.push_back(i);
	}
	if (vec.size() < 3)
	{
		return -1;
	}
	return vec.at(2);
}

float Game::getTime(std::string t_time)
{
	not_digit notADigit;
	string::iterator end = std::remove_if(t_time.begin(), t_time.end(), notADigit);
	string all_numbers(t_time.begin(), end);

	stringstream ss(all_numbers);
	vector<int> vec;
	int i;
	for (; ss >> i;)
	{
		vec.push_back(i);
	}
	if (vec.size() < 4)
	{
		return -1;
	}
	return vec.at(3);
}
