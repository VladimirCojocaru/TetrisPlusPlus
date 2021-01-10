#include "Highscore.h"
#include <fstream>
#include <sstream>

Highscore::Highscore()
	:m_renderWindowHighscore{ sf::VideoMode{HIGHSCORE_WIDTH, HIGHSCORE_HEIGHT}, "HIGHSCORE" }
{
	if (!m_textureHighscore.loadFromFile("../Resources/Images/highscore.png"))
		std::cout << "Could not load image in Highscore Class !! \n";

	if (!m_fontHighscore.loadFromFile("../Resources/Fonts/arcade_i.ttf"))
		std::cout << "Could not load font in Highscore class !! \n";

	m_textureHighscore.setSmooth(true);
	m_spriteHighscore.setTexture(m_textureHighscore);
	//m_spriteHighscore.setColor(sf::Color(255, 255, 255, 200));
	m_spriteHighscore.setOrigin(0, 0);

	InitializeScorePlayerList();
}

void Highscore::draw()
{
	for (int i = 0; i < MAX_NUMBER_PLAYERS; i++)
	{
		m_renderWindowHighscore.draw(m_playersList[i]);
	}
}

void Highscore::runHighscore()
{
	FileReader();
	while (m_renderWindowHighscore.isOpen())
	{
		sf::Event e;
		while (m_renderWindowHighscore.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				m_renderWindowHighscore.close();
			}
		}
		m_renderWindowHighscore.clear();
		m_renderWindowHighscore.draw(m_spriteHighscore);
		draw();
		m_renderWindowHighscore.display();
	}
}

void Highscore::InitializeScorePlayerList()
{
	for (int i = 0; i < MAX_NUMBER_PLAYERS; i++)
	{
		m_playersList[i].setFont(m_fontHighscore);
		m_playersList[i].setFillColor(sf::Color(55, 205, 55));
		m_playersList[i].setOutlineColor(sf::Color::Black);
		m_playersList[i].setOutlineThickness(3);
		m_playersList[i].setCharacterSize(19);
		m_playersList[i].setString("Unknown   0");
		m_playersList[i].setPosition(sf::Vector2f(HIGHSCORE_WIDTH / 3, HIGHSCORE_HEIGHT / 18 * i + 265));
	}

	m_playersList[0].setFillColor(sf::Color::Red);
	m_playersList[1].setFillColor(sf::Color(128, 0, 128));
	m_playersList[2].setFillColor(sf::Color(210, 89, 75));
	m_playersList[3].setFillColor(sf::Color(255, 165, 0));
	m_playersList[4].setFillColor(sf::Color::Yellow);
}


void Highscore::FileReader()
{
	std::ifstream readFile("out.txt");
	if (readFile.is_open())
	{
		std::string line;
		uint16_t index = 0;
		std::vector<std::pair<std::string, std::string>> playersVector;
		for (std::string line; getline(readFile, line);)
		{
			std::istringstream wordbyword(line);
			std::string name;
			std::string score;
			std::getline(wordbyword, name, ' ');
			std::getline(wordbyword, score);
			while (name.size() != 10)
				name += " ";
			std::pair<std::string, std::string> player;
			player.first = name;
			player.second = score;
			playersVector.push_back(player);
		}

		std::sort(playersVector.begin(), playersVector.end(), m_comparePlayers);

		for (std::pair<std::string, std::string> player : playersVector)
			if (index < MAX_NUMBER_PLAYERS)
			{
				m_playersList[index].setString(playersVector.at(index).first + playersVector.at(index).second);
				index++;
			}

		readFile.close();
	}
	else
		std::cout << "File was not open!";
}