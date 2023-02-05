#pragma once
#include <vector>
#include <array>

class CSameGameBoard
{
private:
	int32_t m_width;							// ������ ������
	int32_t m_height;							// ������ ������

	int32_t m_rows;								// ���-�� ����� � ������
	int32_t m_cols;								// ���-�� ����� � �������

	std::vector<std::vector<int32_t>> m_cells;	// ������ �������� ����
	std::array<COLORREF, 8> m_colors;			// ���� �����

	int32_t m_count_colors;						// ���-�� ������ ����� �� ������� ����

private:
	// ������ ����������� ������ �� ������� ����
	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		MAX_VALUE_DIRECTION
	};

public:
	/* ������������ � ���������� */

	CSameGameBoard();
	~CSameGameBoard();

	/* ������ */

	// �������� ����� ������� ����� ����� ����� ����
	void setup_board();
	// �������� ����� �� ������� ����
	void create_cells();
	// ������� ���������� �����
	void delete_cells(int32_t &row, int32_t &col);
	// �������� �������� �����
	void delete_neighbor_cells(int32_t row, int32_t col, int32_t color, Direction direction);
	// ������� ������� �����
	void delete_board();

	/* ������� */

	// ��������� ����� ������� ������
	COLORREF get_colors(int32_t &row, int32_t &col) const;
	// ��������� ���-�� ����� � ������
	int32_t get_rows()		 const	{ return m_rows;   }	
	// ��������� ���-�� ����� � �������
	int32_t get_cols()		 const	{ return m_cols;   }
	// ��������� ������ �������� ����
	int32_t get_width()		 const	{ return m_width;  }	
	// ��������� ������ �������� ����
	int32_t get_height()	 const	{ return m_height; }
	// ��������� ���-�� ������
	int32_t get_num_colors() const	{ return m_count_colors; }

	/* ������� */

	// ��������� ������ ���-�� ������ ��� ����� �� ������� ����
	void set_num_colors(int32_t &count_colors);
	// ��������� ������ ���-�� ����� �� ������� ����
	void set_cells_count(int32_t &count_cols);
	// ��������� ������ ������� ����� �� ������� ����
	void set_cells_size(int32_t &cells_size);
};