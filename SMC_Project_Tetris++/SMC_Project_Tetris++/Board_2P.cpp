#include "Board_2P.h"

Board_2P::Board_2P(Position size, IGame& game)
	:IBoard{ size, game }
{
}

void Board_2P::MarkLinesForRemoval()
{

	if (m_ToRemoveBlocks)
		return;
	int countClearedLines = 0;
	for (int y = m_Size.y - 1; y > 0; y--)
	{
		int counter = 0;
		for (int x = 0; x < m_Size.x; x++)
		{
			auto field = GetField(x, y);
			if (field->m_Occupied)
				counter++;
			if (counter == BOARD_WIDTH_2P) // Line full
			{
				m_ToBeCleaned.push_back(y);
				m_ToRemoveBlocks = true;
				countClearedLines++;
			}
		}
		counter = 0;
	}
	m_Game.m_score.AddClearedLines(countClearedLines);
	std::sort(m_ToBeCleaned.begin(), m_ToBeCleaned.end(), [](int left, int right) { return left < right; });
}
