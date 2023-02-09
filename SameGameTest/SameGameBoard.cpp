#include "pch.h"
#include "SameGameBoard.h"
#include <random>

CSameGameBoard::CSameGameBoard() : m_cells{}, 
m_width{50}, m_height{50},
m_rows{15}, m_cols{15},
m_count_colors{3}, m_count_cells{}
{
	// ������������� ����������� ���� ��� ������ ������ ������� ������
	m_colors.at(0) = RGB(255, 255, 255);	// White Color
	m_colors.at(1) = RGB(0, 0, 255);		// Blue Color
	m_colors.at(2) = RGB(255, 194, 0);		// Yellow Color
	m_colors.at(3) = RGB(255, 79, 0);		// Orange Color
	m_colors.at(4) = RGB(255, 0, 0);		// Red Color
	m_colors.at(5) = RGB(167, 64, 255);		// Purple Color
	m_colors.at(6) = RGB(12, 93, 165);		// Light Blue Color
	m_colors.at(7) = RGB(122, 236, 73);		// Green Color
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
	for (size_t rows{}; rows < m_rows; ++rows)
		for (size_t cols{}; cols < m_cols; ++cols)
			// ������������� �������� ���������� ����� ����� (���� ���� �� ���������)
			m_cells.at(rows).at(cols) = 1 + std::mt19937(std::random_device {}())() % m_count_colors;

	// ���� ����� ���-�� ����� �� ������� ���� ����� ��� ����������
	m_count_cells = m_rows * m_cols;
}

void CSameGameBoard::create_cells()
{
	// ������� ������� �����
	delete_board();
	// ��������� ������ ��� ������ ������� �����
	m_cells.assign(m_rows, std::vector<int32_t>(m_cols));
}

bool CSameGameBoard::is_game_over()
{
	// ������������ �� ���� ������� � �������� �������� ���� (�����-������� �����-�����)
	for (int32_t cols{}; cols < m_cols; ++cols) {
		for (int32_t rows{m_rows-1}; rows >= 0; --rows) {
			// ���� �� ������ �� ������ � ������ ����, �� ��� ������, ��� ������� ��� ���������
			if (m_cells.at(rows).at(cols) == 0) break;

			// �������� �� ����� �� �������
			if (rows - 1 < 0 || cols + 1 > m_cols) continue;

			// ��������� �������� ������ ������ � ������. ���������� false, ���� ���� �� ���� �� ��� ����� ����� ��������
			if (m_cells.at(rows - 1).at(cols) == m_cells.at(rows).at(cols) ||
				m_cells.at(rows).at(cols + 1) == m_cells.at(rows).at(cols)) return false;
		}
	}
	// ���� �� ����� � ����������� ��������� ������� ���, ���������� true
	return true;
}

void CSameGameBoard::cells_move_down()
{
	bool flag = true;			// �������� �� ������������ ������
	// �������� ������ ������ �� ���� ������������ �� ��� ���, ���� �� ��������� ������� ����
	while (flag)
	{
		// �������� �������� ����� ����� ������� ������ ������� �� �������� ����
		flag = false;
		// C���� ����� ���� - ������ ������ ��������� �� �����, ����� �� ����� �� �������
		for (size_t rows{1}; rows < m_rows; ++rows) {
			for (size_t cols{}; cols < m_cols; ++cols) {
				// ��� ������ �� ����� �� ������� ���� ������ ������, �������� �������� �� �� ������, ��� ����
				if (m_cells.at(rows).at(cols) == 0 && m_cells.at(rows - 1).at(cols) != 0) {
					// ���������� ������ � ������ 1 �� ����, �.�. �� ����� ������ ��� ������
					std::swap(m_cells.at(rows - 1).at(cols), m_cells.at(rows).at(cols)); flag = true;
				}
			}
		}
	}
}

void CSameGameBoard::cells_move_left()
{
	int32_t last_cols{};		// ������������ � ����� ������
	bool flag = true;			// �������� �� ������������ ������
	while (flag)
	{
		flag = false; last_cols++;
		// �������� ����� ����� - ������� ������ ������� �� ���� ������� 
		// (� ���� ������ ���� �������������� ������ ������ ������)
		for (size_t cols {}; cols < m_cols; ++cols) {
			// ���� ������ ������, ������� � ������ ����� �������� ����
			if (m_cells.at(0).at(cols) != 0) continue;

			// ���� �� ����� ����� ������, �� ������� ���� �� �������
			for (size_t rows {}; rows < m_rows; ++rows) {
				// ���� ���� �� ���� �� ����� �������, ����� �� ������� �� ����� � ��������� ������ �������
				if (m_cells.at(rows).at(cols) != 0) break;
				// ��������, ��� � ������� ��� ����� ������, � ������ ��� ������������
				if (rows != m_rows - 1 || cols >= m_cols - last_cols) continue;

				// ���� � ������ ��� ����� ������, �������� ������
				for (size_t rows{}; rows < m_rows; ++rows) {
					// ������ ���� ������� �������� ���� � ������
					std::swap(m_cells.at(rows).at(cols + 1), m_cells.at(rows).at(cols)); flag = true;
				}
			}
		}
	}
}

void CSameGameBoard::compact_board()
{
	cells_move_down();
	cells_move_left();
}

void CSameGameBoard::delete_cells(int32_t &row, int32_t &col)
{
	// ���-�� ��������� �����
	int32_t count_delete_cells{};

	// ������ ���� �����, ������� ����� ������� (�� ����� ����� ��������� ������)
	int32_t color_cells = m_cells.at(row).at(col);

	// ���� ���� ����� 0, ������ �� ������ �� ������ ������
	if (color_cells == 0) return;

	// �������� ������� ������ ����������� ����� �� ������ ��������� ������
	delete_neighbor_cells(row - 1, col, color_cells, count_delete_cells);	// �����
	delete_neighbor_cells(row + 1, col, color_cells, count_delete_cells);	// ����
	delete_neighbor_cells(row, col - 1, color_cells, count_delete_cells);	// �����
	delete_neighbor_cells(row, col + 1, color_cells, count_delete_cells);	// ������

	// ����� �������� ���� ����� �������� ��������� ������
	compact_board();

	// ����� ���� �������� �� ������� � ���������� ������ ���� ���������� ���-�� ������
	m_count_cells -= count_delete_cells;
}

void CSameGameBoard::delete_neighbor_cells(int32_t row, int32_t col, int32_t color, int32_t &count_delete_cells)
{
	// �������� �� ����� �� �������
	if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) return;

	// �������� �� ��, ��� ���� ����� �� ��������� � ����������
	if (m_cells.at(row).at(col) != color) return;

	// ����������� ���-�� ������ ��������� ������
	count_delete_cells++;

	// ���� ������ ������ ����� ����� ������ ������, ������� ������� ������
	m_cells.at(row).at(col) = 0;

	// ������ ������ �� ���� ������ �������� �����
	delete_neighbor_cells(row - 1, col, color, count_delete_cells);    // �����
	delete_neighbor_cells(row + 1, col, color, count_delete_cells);    // ����
	delete_neighbor_cells(row, col - 1, color, count_delete_cells);	   // �����
	delete_neighbor_cells(row, col + 1, color, count_delete_cells);    // ������
}

void CSameGameBoard::delete_board()
{
	// ���� ������� ���� ���������, ������ ������� �����
	if (!m_cells.empty()) m_cells.clear();
}

COLORREF CSameGameBoard::get_colors(int32_t &row, int32_t &col) const
{
	// ���� ���������� �������������, ������ �� ������������ ������ ���
	if (row < 0 || col < 0) return m_colors.at(0);
	// ���������� ����, ������� ������������ �� ������� ������� �������� ����
	return m_colors.at(m_cells.at(row).at(col));
}

void CSameGameBoard::set_count_colors(int32_t &count_colors)
{
	// ������������� �� ���� ���-�� ������, ������ ����������� ���-��. ���� �� 
	// ������� �� ������� �������, �� ���������� ������� ���-�� ������
	m_count_colors = (count_colors >= 3 && count_colors <= 7) ? count_colors : m_count_colors;
}

void CSameGameBoard::set_cells_count(int32_t &count_cols)
{
	m_cols = m_rows = static_cast<int32_t>(sqrt(count_cols));
}

void CSameGameBoard::set_cells_size(int32_t &cells_size)
{
	m_width = m_height = cells_size;
}