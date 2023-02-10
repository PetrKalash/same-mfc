#pragma once
#include <vector>
#include <array>

class CSameGameBoard
{
private:
	std::vector<std::vector<int32_t>> m_cells;	// €чейки игрового пол€
	std::array<COLORREF, 8> m_colors;			// цвет €чеек

	int32_t m_width;							// ширина €чейки
	int32_t m_height;							// высота €чейки

	int32_t m_rows;								// кол-во €чеек у строки
	int32_t m_cols;								// кол-во €чеек у столбца

	int32_t m_count_colors;						// кол-во цветов €чеек на игровом поле
	int32_t m_count_cells;						// кол-во оставшихс€ €чеек на игровом поле

public:
	/*  онструкторы и деструктор */

	//  онструктор по умолчанию
	CSameGameBoard();
	//  онструктор глубокого копировани€
	CSameGameBoard(const CSameGameBoard &board);
	// ƒеструктор
	~CSameGameBoard();

	/* ћетоды */

	// —оздание новой игровой доски после конца игры
	void setup_board();
	// —оздание €чеек на игровом поле
	void create_cells();
	// ѕроверка на конец игры
	bool is_game_over();
	// —двиг €чеек вниз
	void cells_move_down();
	// —двиг €чеек влево
	void cells_move_left();
	//  омпактный сдвиг игровой доски после удалени€ €чеек
	void compact_board();
	// ќчистка одинаковых €чеек
	void delete_cells(int32_t &row, int32_t &col);
	// ”даление соседних €чеек
	void delete_neighbor_cells(int32_t row, int32_t col, int32_t color, int32_t &count_delete_cells);
	// ќчистка игровой доски
	void delete_board();

	/* √еттеры */

	// ѕолучение цвета игровой €чейки
	COLORREF get_colors(int32_t &row, int32_t &col) const;
	// ѕолучение кол-ва €чеек у строки
	int32_t get_rows()		 const	{ return m_rows;   }	
	// ѕолучение кол-ва €чеек у столбца
	int32_t get_cols()		 const	{ return m_cols;   }
	// ѕолучение ширины игрового пол€
	int32_t get_width()		 const	{ return m_width;  }	
	// ѕолучение высоты игрового пол€
	int32_t get_height()	 const	{ return m_height; }
	// ѕолучение кол-ва цветов
	int32_t get_num_colors() const	{ return m_count_colors; }	
	// ѕолучение кол-ва €ччек на игровом поле
	int32_t get_count_cells() const	{ return m_count_cells; }

	/* —еттеры */

	// ”становка нового кол-ва цветов дл€ €чеек на игровом поле
	void set_count_colors(int32_t &count_colors);
	// ”становка нового кол-ва €чеек на игровом поле
	void set_cells_count(int32_t &count_cols);
	// ”становка нового размера €чеек на игровом поле
	void set_cells_size(int32_t &cells_size);
};