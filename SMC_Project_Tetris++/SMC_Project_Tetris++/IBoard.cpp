#include "IBoard.h"
#include <iostream>
#include <fstream>
#include <algorithm>

FieldData::FieldData(sf::Texture& texture, uint16_t id)
{
	sf::IntRect rectangle{ (id % TEXTURES_NUMBER) * 18, 0, 18, 18 };
	m_sprite.setTexture(texture);
	m_sprite.setTextureRect(rectangle);
}

Field& Field::operator=(const Field& field)
{
	this->m_occupied = field.m_occupied;
	this->m_visible = field.m_visible;
	this->m_info = field.m_info;
	this->m_darkHole = field.m_darkHole;
	
	return *this;
}

IBoard::IBoard(Position size, IGame& game)
	: m_game{ game }, m_fields{}, m_fieldDatas{}, m_size{ size }, m_toBeCleaned{}, m_elapsedTime{ 0.f }, m_toRemoveBlocks{ false }
{
	for (int x = 0; x < size.x; x++)
		for (int y = 0; y < size.y; y++)
			m_fields[Convert2DTo1D(x, y)] = std::make_unique<Field>();

	for (int id = 0; id < TEXTURES_NUMBER; id++)
		m_fieldDatas[id] = std::make_unique<FieldData>(m_game.m_texture, id);
}

void IBoard::Update(const sf::Time& dt)
{
	MarkLinesForRemoval();
	if (m_toRemoveBlocks)
	{
		m_elapsedTime += dt.asSeconds();
		Blink();
		if (m_elapsedTime > 0.6f)
		{
			m_elapsedTime = 0.f;
			CleanLines();
		}
	}
}

void IBoard::Clean()
{
	for (uint16_t x = 0; x < m_size.x; x++)
	{
		for (uint16_t y = 0; y < m_size.y; y++)
		{
			auto field = GetField(x, y);
			field->m_occupied = false;
			field->m_visible = true;
			field->m_info = nullptr;
		}
	}
}

void IBoard::AddBlock(uint16_t id, std::array<Position, BLOCK_ARRAY_COLUMNS> block)
{
	for (int i = 0; i < BLOCK_ARRAY_COLUMNS; i++)
	{
		auto field = GetField(block[i].x, block[i].y);
		field->m_occupied = true;
		field->m_info = m_fieldDatas[id].get();
	}
}

bool IBoard::IsOccupied(std::array<Position, BLOCK_ARRAY_COLUMNS> block)
{
	for (int i = 0; i < BLOCK_ARRAY_COLUMNS; i++)
	{
		auto field = GetField(block[i].x, block[i].y);
		if (field->m_darkHole)
			return false;

		if (field->m_occupied)
			return true;
	}
	return false;
}

Field* IBoard::GetField(const uint16_t x, const uint16_t y)
{
	return m_fields[Convert2DTo1D(x, y)].get();
}

void IBoard::Draw(sf::RenderWindow& window)
{
	for (int x = 0; x < m_size.x; x++)
		for (int y = 0; y < m_size.y; y++)
		{
			auto field = GetField(x, y);

			//if field isn't occupied yet, m_Info is set to nullptr
			if (field->m_occupied && field->m_visible)
			{
				field->m_info->m_sprite.setPosition(x * 18.f, y * 18.f);
				window.draw(field->m_info->m_sprite);
			}
		}
}


int IBoard::Convert2DTo1D(const uint16_t x, const uint16_t y)
{
	return (y * m_size.x + x);
}

void IBoard::CleanLines()
{
	if (m_toBeCleaned.empty())
		return;

	if (!m_clearLinesMusic.openFromFile("../Resources/Sounds/clear.wav"))
		std::cout << "Could not load music in Board Interface !! \n";

	m_clearLinesMusic.play();

	for (auto i : m_toBeCleaned)
	{
		for (auto y = i; y >= 0; y--)
		{
			for (auto x = 0; x < m_size.x; x++)
			{
				int up = y - 1;
				if (up < 0)
					continue;
				*GetField(x, y) = *GetField(x, up);
			}
		}
	}
	m_toBeCleaned.clear();
	m_toRemoveBlocks = false;
	m_game.m_gameplayMusic.play();
}

void IBoard::Blink()
{
	//Speeds up blinking

	int num = int(m_elapsedTime * 5.f);
	for (auto y : m_toBeCleaned)
		for (int x = 0; x < m_size.x; x++)
			GetField(x, y)->m_visible = (num % 2 != 0);
}

void IBoard::AddSpecialBlock(uint16_t id, Position block)
{
	auto field = GetField(block.x, block.y);
	field->m_occupied = true;
	field->m_info = m_fieldDatas[id].get();
}
