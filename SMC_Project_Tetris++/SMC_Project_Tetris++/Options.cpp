#include "Options.h"

Options::Options()
	: m_renderWindowOptions{ sf::VideoMode{OPTIONS_WIDTH, OPTIONS_HEIGHT}, "OPTIONS" }, m_page{ 1 }
{
	if (!m_textureOptions.loadFromFile("../Resources/Images/optionsTetrisEffect.jpg"))
		std::cout << "Could not load image in Options Class !! \n";

	if (!m_fontOptions.loadFromFile("../Resources/Fonts/arial.ttf"))
		std::cout << "Could not load font in Options class !! \n";

	m_textureOptions.setSmooth(true);
	m_spriteOptions.setTexture(m_textureOptions);
	m_spriteOptions.setColor(sf::Color(255, 255, 255, 158));
	m_spriteOptions.setOrigin(0, 0);

	InitializeControlsSingleplayerGame();
	InitializeControlsMultiplayerGame();
	InitializeControlSound();
	InitializeTextPage();

}

void Options::draw(uint16_t& levelSound)
{
	if (m_page == 1)
	{
		for (uint8_t i = 0; i < MAX_NUMBER_CONTROLS; i++)
		{
			m_renderWindowOptions.draw(m_controlsSingleplayerGame[i]);
		}
		m_renderWindowOptions.draw(m_textPage[0]);
	}
	else
	{
		for (uint8_t i = 0; i < MAX_NUMBER_CONTROLS_MP; i++)
		{
			m_renderWindowOptions.draw(m_controlsMultiplayerGame[i]);
		}
		m_renderWindowOptions.draw(m_textPage[1]);
	}
	m_renderWindowOptions.draw(m_controlSound[levelSound]);
}

void Options::RunOptions(uint16_t& levelSound)
{
	while (m_renderWindowOptions.isOpen())
	{
		sf::Event e;
		while (m_renderWindowOptions.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				m_renderWindowOptions.close();
			}
			else if (e.type == sf::Event::KeyPressed)
			{

				if (e.key.code == sf::Keyboard::Escape)
				{
					m_renderWindowOptions.close();
				}
				if (e.key.code == sf::Keyboard::Up)
				{
					if (levelSound < 5)
						levelSound++;
				}
				if (e.key.code == sf::Keyboard::Down)
				{
					if (levelSound > 0)
						levelSound--;
				}
				if (e.key.code == sf::Keyboard::Left)
				{
					if (m_page > 1)
						m_page--;
				}
				if (e.key.code == sf::Keyboard::Right)
				{
					if (m_page < 2)
						m_page++;
				}
			}
		}
		m_renderWindowOptions.clear();
		m_renderWindowOptions.draw(m_spriteOptions);
		draw(levelSound);
		m_renderWindowOptions.display();
	}
}

Options::~Options()
{
}

void Options::InitializeControlsSingleplayerGame()
{
	m_controlsSingleplayerGame[0].setFont(m_fontOptions);
	m_controlsSingleplayerGame[0].setFillColor(sf::Color::Green);
	m_controlsSingleplayerGame[0].setOutlineColor(sf::Color::Black);
	m_controlsSingleplayerGame[0].setOutlineThickness(3);
	m_controlsSingleplayerGame[0].setCharacterSize(30);
	m_controlsSingleplayerGame[0].setString("Controls in SP game");
	m_controlsSingleplayerGame[0].setPosition(sf::Vector2f(OPTIONS_WIDTH / 12, OPTIONS_HEIGHT / 15));

	for (uint8_t i = 1; i < MAX_NUMBER_CONTROLS; i++)
	{
		m_controlsSingleplayerGame[i].setFont(m_fontOptions);
		if (i > MAX_NUMBER_CONTROLS - 4)
			m_controlsSingleplayerGame[i].setFillColor(sf::Color::White);
		else
			m_controlsSingleplayerGame[i].setFillColor(sf::Color::Yellow);
		m_controlsSingleplayerGame[i].setOutlineColor(sf::Color::Black);
		m_controlsSingleplayerGame[i].setOutlineThickness(3);
		m_controlsSingleplayerGame[i].setCharacterSize(15);
		m_controlsSingleplayerGame[i].setPosition(sf::Vector2f(OPTIONS_WIDTH / 8, OPTIONS_HEIGHT / 15 * (i + 1.5)));
	}

	m_controlsSingleplayerGame[1].setString("Arrow Down = piece go down");
	m_controlsSingleplayerGame[2].setString("Arrow Left = piece go left");
	m_controlsSingleplayerGame[3].setString("Arrow Right = piece go right");
	m_controlsSingleplayerGame[4].setString("Arrow Up = piece rotate");
	m_controlsSingleplayerGame[5].setString("A = piece scale up");
	m_controlsSingleplayerGame[6].setString("Z = piece scale down");
	m_controlsSingleplayerGame[7].setString("Escape = return to menu");
	m_controlsSingleplayerGame[8].setString("Space = pause game");
	m_controlsSingleplayerGame[9].setString("H (in pause menu) = highscore");

}

void Options::InitializeControlsMultiplayerGame()
{
	m_controlsMultiplayerGame[0].setFont(m_fontOptions);
	m_controlsMultiplayerGame[0].setFillColor(sf::Color::Green);
	m_controlsMultiplayerGame[0].setOutlineColor(sf::Color::Black);
	m_controlsMultiplayerGame[0].setOutlineThickness(3);
	m_controlsMultiplayerGame[0].setCharacterSize(30);
	m_controlsMultiplayerGame[0].setString("Controls in MP game");
	m_controlsMultiplayerGame[0].setPosition(sf::Vector2f(OPTIONS_WIDTH / 5, OPTIONS_HEIGHT / 15));

	m_controlsMultiplayerGame[1].setFont(m_fontOptions);
	m_controlsMultiplayerGame[1].setFillColor(sf::Color::Yellow);
	m_controlsMultiplayerGame[1].setOutlineColor(sf::Color::Black);
	m_controlsMultiplayerGame[1].setOutlineThickness(3);
	m_controlsMultiplayerGame[1].setCharacterSize(20);
	m_controlsMultiplayerGame[1].setString("Player 1");
	m_controlsMultiplayerGame[1].setPosition(sf::Vector2f(OPTIONS_WIDTH / 10, OPTIONS_HEIGHT / 15 * 2));

	m_controlsMultiplayerGame[2].setFont(m_fontOptions);
	m_controlsMultiplayerGame[2].setFillColor(sf::Color::Cyan);
	m_controlsMultiplayerGame[2].setOutlineColor(sf::Color::Black);
	m_controlsMultiplayerGame[2].setOutlineThickness(3);
	m_controlsMultiplayerGame[2].setCharacterSize(20);
	m_controlsMultiplayerGame[2].setString("Player 2");
	m_controlsMultiplayerGame[2].setPosition(sf::Vector2f(OPTIONS_WIDTH / 10 * 5.5, OPTIONS_HEIGHT / 15 * 2));

	for (uint8_t i = 3; i < MAX_NUMBER_CONTROLS_MP / 2; i++)
	{
		m_controlsMultiplayerGame[i].setFont(m_fontOptions);
		m_controlsMultiplayerGame[i].setFillColor(sf::Color::Yellow);
		m_controlsMultiplayerGame[i].setOutlineColor(sf::Color::Black);
		m_controlsMultiplayerGame[i].setOutlineThickness(3);
		m_controlsMultiplayerGame[i].setCharacterSize(15);
		m_controlsMultiplayerGame[i].setPosition(sf::Vector2f(OPTIONS_WIDTH / 10, OPTIONS_HEIGHT / 20 * (i + 2)));
	}

	for (uint8_t i = MAX_NUMBER_CONTROLS_MP / 2; i < MAX_NUMBER_CONTROLS_MP - 3; i++)
	{
		m_controlsMultiplayerGame[i].setFont(m_fontOptions);
		m_controlsMultiplayerGame[i].setFillColor(sf::Color::Cyan);
		m_controlsMultiplayerGame[i].setOutlineColor(sf::Color::Black);
		m_controlsMultiplayerGame[i].setOutlineThickness(3);
		m_controlsMultiplayerGame[i].setCharacterSize(15);
		m_controlsMultiplayerGame[i].setPosition(sf::Vector2f(OPTIONS_WIDTH / 10 * 5.5, OPTIONS_HEIGHT / 20 * (i - 6 + 2)));
	}

	for (uint8_t i = MAX_NUMBER_CONTROLS_MP - 3; i < MAX_NUMBER_CONTROLS_MP; i++)
	{
		m_controlsMultiplayerGame[i].setFont(m_fontOptions);
		m_controlsMultiplayerGame[i].setFillColor(sf::Color::White);
		m_controlsMultiplayerGame[i].setOutlineColor(sf::Color::Black);
		m_controlsMultiplayerGame[i].setOutlineThickness(3);
		m_controlsMultiplayerGame[i].setCharacterSize(15);
		m_controlsMultiplayerGame[i].setPosition(sf::Vector2f(OPTIONS_WIDTH / 3, OPTIONS_HEIGHT / 20 * (i - 6 + 2)));
	}

	//Controls for player 1
	m_controlsMultiplayerGame[3].setString(" S = piece go down ");
	m_controlsMultiplayerGame[4].setString(" A = piece go left");
	m_controlsMultiplayerGame[5].setString(" D = piece go right");
	m_controlsMultiplayerGame[6].setString(" W = piece rotate");
	m_controlsMultiplayerGame[7].setString(" R = piece scale up");
	m_controlsMultiplayerGame[8].setString(" F = piece scale down");

	//Controls for player 2
	m_controlsMultiplayerGame[9].setString("Arrow Down = piece go down");
	m_controlsMultiplayerGame[10].setString("Arrow Left = piece go left");
	m_controlsMultiplayerGame[11].setString("Arrow Right = piece go right");
	m_controlsMultiplayerGame[12].setString("Arrow Up = piece rotate");
	m_controlsMultiplayerGame[13].setString("Numpad1 = piece scale up");
	m_controlsMultiplayerGame[14].setString("Numpad0 = piece scale down");

	//System controls
	m_controlsMultiplayerGame[15].setString("Escape = return to menu");
	m_controlsMultiplayerGame[16].setString("Space = pause game");
	m_controlsMultiplayerGame[17].setString("H (in pause menu) = highscore");
}

void Options::InitializeControlSound()
{
	for (auto& controlSound : m_controlSound)
	{
		controlSound.setFont(m_fontOptions);
		controlSound.setFillColor(sf::Color::Red);
		controlSound.setOutlineColor(sf::Color::Black);
		controlSound.setOutlineThickness(5);
		controlSound.setCharacterSize(25);
		controlSound.setPosition(sf::Vector2f(OPTIONS_WIDTH / 12, OPTIONS_HEIGHT / 15 * 12));
	}

	m_controlSound[0].setString("Sound mute");
	m_controlSound[1].setString("Sound 20%");
	m_controlSound[2].setString("Sound 40%");
	m_controlSound[3].setString("Sound 60%");
	m_controlSound[4].setString("Sound 80%");
	m_controlSound[5].setString("Sound 100%");
}

void Options::InitializeTextPage()
{
	for (auto& textPage : m_textPage)
	{
		textPage.setFont(m_fontOptions);
		textPage.setFillColor(sf::Color::White);
		textPage.setOutlineColor(sf::Color::Black);
		textPage.setOutlineThickness(5);
		textPage.setCharacterSize(15);
		textPage.setPosition(sf::Vector2f(OPTIONS_WIDTH / 2.5, OPTIONS_HEIGHT / 15 * 14));
	}

	m_textPage[0].setString("Page < 1/2 >");
	m_textPage[1].setString("Page < 2/2 >");
}
