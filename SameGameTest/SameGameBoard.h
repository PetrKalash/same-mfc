#pragma once
#include <vector>
#include <array>

class CSameGameBoard
{
private:
	const int32_t m_width;						// ширина €чейки
	const int32_t m_height;						// высота €чейки

	int32_t m_rows;								// кол-во €чеек у строки
	int32_t m_cols;								// кол-во €чеек у столбца

	std::vector<std::vector<int32_t>> m_cells;	// €чейки игрового пол€

	std::array<COLORREF, 4> m_colors;			// цвет €чеек

public:
	/*  онструкторы и деструктор */

	CSameGameBoard();
	~CSameGameBoard();

	/* ћетоды */

	// —оздание новой игровой доски после конца игры
	void setup_board();
	// —оздание €чеек на игровом поле
	void create_cells();
	// ќчистка игровой доски
	void delete_board();

	/* √еттеры */

	// ѕолучение цвета игровой €чейки
	COLORREF get_colors(int32_t &row, int32_t &col);
	// ѕолучение кол-ва €чеек у строки
	int32_t get_rows()	 const	{ return m_rows;   }	
	// ѕолучение кол-ва €чеек у столбца
	int32_t get_cols()	 const	{ return m_cols;   }
	// ѕолучение ширины игрового пол€
	int32_t get_width()  const	{ return m_width;  }	
	// ѕолучение высоты игрового пол€
	int32_t get_height() const	{ return m_height; }
};