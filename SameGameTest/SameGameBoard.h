#pragma once
#include <vector>
#include <array>

class CSameGameBoard
{
private:
	const int32_t m_width;						// ������ ������
	const int32_t m_height;						// ������ ������

	int32_t m_rows;								// ���-�� ����� � ������
	int32_t m_cols;								// ���-�� ����� � �������

	std::vector<std::vector<int32_t>> m_cells;	// ������ �������� ����

	std::array<COLORREF, 4> m_colors;			// ���� �����

public:
	/* ������������ � ���������� */

	CSameGameBoard();
	~CSameGameBoard();

	/* ������ */

	// �������� ����� ������� ����� ����� ����� ����
	void setup_board();
	// �������� ����� �� ������� ����
	void create_cells();
	// ������� ������� �����
	void delete_board();

	/* ������� */

	// ��������� ����� ������� ������
	COLORREF get_colors(int32_t &row, int32_t &col);
	// ��������� ���-�� ����� � ������
	int32_t get_rows()	 const	{ return m_rows;   }	
	// ��������� ���-�� ����� � �������
	int32_t get_cols()	 const	{ return m_cols;   }
	// ��������� ������ �������� ����
	int32_t get_width()  const	{ return m_width;  }	
	// ��������� ������ �������� ����
	int32_t get_height() const	{ return m_height; }
};