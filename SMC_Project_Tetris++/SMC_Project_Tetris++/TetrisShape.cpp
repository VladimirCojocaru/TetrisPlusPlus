#include "TetrisShape.h"

TetrisShape::TetrisShape(uint16_t centerL, uint16_t centerC)
	: m_centerL{centerL}, m_centerC{centerC}, m_color{Color::Red}
{
	//m_piece_array[m_centerL,m_centerC] = 1  // nu inteleg de ce nu imi acceseaza operatorul [] 
	m_piece_array[m_centerL * COLUMNS + m_centerC] = 1;
}

std::optional<int>& TetrisShape::operator[](const Position& position)
{
	const auto& [line, column] = position;
	if (line < ROWS && column < COLUMNS)
		return m_piece_array[line * COLUMNS + column];
	else
		throw "Index out of bounds";
}

const std::optional<int>& TetrisShape::operator[](const Position& position) const
{
	const auto& [line, column] = position;
	if (line < ROWS && column < COLUMNS)
		return m_piece_array[line * COLUMNS + column];
	else
		throw "Index out of bounds";
}

std::ostream& operator<<(std::ostream& outFlux, TetrisShape& shape)
{
	TetrisShape::Position position;
	auto& [line, column] = position;

	for (line = 0; line < TetrisShape::ROWS; line++)
	{
		for (column = 0; column < TetrisShape::COLUMNS ; column++)
		{
			if (const auto& optInt = shape[position]; optInt.has_value())
				outFlux << optInt.value() << " ";
			else
				outFlux << "-" << " ";
		}
		outFlux << std::endl;
	}
	return outFlux;
}