#include "pch.h"
#include "SameGameBoard.h"
#include <random>

CSameGameBoard::CSameGameBoard() : m_cells{}, 
m_width{50}, m_height{50},
m_rows{15}, m_cols{15}
{
	// ������������� ����������� ���� ��� ������ ������ ������� ������
	m_colors.at(0) = RGB(202, 202, 202);			// Black Color
	m_colors.at(1) = RGB(255, 0, 0);		// White Color
	m_colors.at(2) = RGB(254, 254, 254);	// Red Color
	m_colors.at(3) = RGB(0, 0, 255);		// Blue Color
}

CSameGameBoard::~CSameGameBoard()
{
	delete_board();
}

void CSameGameBoard::setup_board()
{
	// ���� ������ �� ������� ���� ��� �� �������������, ������� ����� ����
	create_cells();

	// ������������ �� ���� ������� � �������� �������� ����
	for (size_t rows{}; rows < m_width; ++rows)
		for (size_t cols{}; cols < m_width; ++cols)
			// ������������� �������� ���������� ����� ����� (���� ���� �� ���������)
			m_cells.at(rows).at(cols) = 1 + std::mt19937(std::random_device {}())() % 3;
}

void CSameGameBoard::create_cells()
{
	// ������� ������� �����
	delete_board();
	// ��������� ������ ��� ������ ������� �����
	m_cells.assign(m_width, std::vector<int32_t>(m_height));
}

void CSameGameBoard::delete_board()
{
	// ���� ������� ���� ���������, ������ ������� �����
	if (!m_cells.empty()) m_cells.clear();
}

COLORREF CSameGameBoard::get_colors(int32_t &row, int32_t &col)
{
	// ���� ���������� �������������, ������ �� ������������ ������ ���
	if (row < 0 || col < 0) return m_colors.at(0);
	// ���������� ����, ������� ������������ �� ������� ������� �������� ����
	return m_colors.at(m_cells.at(row).at(col));
}