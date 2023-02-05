#include "pch.h"
#include "SameGameBoard.h"
#include <random>

CSameGameBoard::CSameGameBoard() : m_cells{}, 
m_width{50}, m_height{50},
m_rows{15}, m_cols{15},
m_count_colors{3}
{
	// Устанавливаем собственный цвет для каждой ячейки массива цветов
	m_colors.at(0) = RGB(202, 202, 202);	// Black Color
	m_colors.at(1) = RGB(255, 0, 0);		// White Color
	m_colors.at(2) = RGB(254, 254, 254);	// Red Color
	m_colors.at(3) = RGB(0, 0, 255);		// Blue Color
	m_colors.at(4) = RGB(255, 104, 23);		// Orange Color
	m_colors.at(5) = RGB(167, 64, 255);		// Purple Color
	m_colors.at(6) = RGB(122, 236, 73);		// Green Color
	m_colors.at(7) = RGB(255, 240, 73);		// Yellow Color
}

CSameGameBoard::~CSameGameBoard()
{
	delete_board();
}

void CSameGameBoard::setup_board()
{
	// Если ячейки на игровом поле еще не сгенерированы, создаем новое поле
	create_cells();

	// Перебираемся по всем строкам и столбцам игрового поля
	for (size_t rows{}; rows < m_width; ++rows)
		for (size_t cols{}; cols < m_width; ++cols)
			// Устанавливаем значение случайного цвета блока (цвет фона не учитываем)
			m_cells.at(rows).at(cols) = 1 + std::mt19937(std::random_device {}())() % m_count_colors;
}

void CSameGameBoard::create_cells()
{
	// Очистка игровой доски
	delete_board();
	// Выделение памяти под ячейки игровой доски
	m_cells.assign(m_width, std::vector<int32_t>(m_height));
}

void CSameGameBoard::delete_cells(int32_t &row, int32_t &col)
{
	// Узнаем цвет ячеек, которые нужно удалять (он будет равен выбранной ячейке)
	int32_t color_cells = m_colors.at(m_cells.at(row).at(col));

	// Если цвет равен 0, значит мы нажали по пустой ячейке
	if (color_cells == 0) return;

	// Начинаем удалять ячейки одинакового цвета сверху
	delete_neighbor_cells(row - 1, col, color_cells, Direction::UP);
}

void CSameGameBoard::delete_neighbor_cells(int32_t row, int32_t col, int32_t color, Direction direction)
{
	switch (direction)
	{
		// Проходимся по всем ячейкам и удаляем соседние
		case Direction::UP:
		{
			// Если ячейка сверху равна цвету первой ячейки, начинаем проход вверх
			if (m_cells.at(row).at(col) == color)
			{
				// Удаляем ячейку сверху
				m_cells.at(row).at(col) = 0;

				// Удаляем соседни ячейки справа и слева
				m_cells.at(row).at(col) = 0;
			}
			break;
		}
		default: break;
	}
}

void CSameGameBoard::delete_board()
{
	// Если игровое поле заполнено, делаем очистку ячеек
	if (!m_cells.empty()) m_cells.clear();
}

COLORREF CSameGameBoard::get_colors(int32_t &row, int32_t &col) const
{
	// Если координаты отрицательные, значит мы отрисовываем задний фон
	if (row < 0 || col < 0) return m_colors.at(0);
	// Возвращаем цвет, который сгенерирован на текущей позиции игрового поля
	return m_colors.at(m_cells.at(row).at(col));
}

void CSameGameBoard::set_num_colors(int32_t &count_colors)
{
	// Устанавливаем на поле кол-во цветов, равное переданному кол-ву. Если мы 
	// выходим за игровые пределы, то возвращаем текущее кол-во цветов
	m_count_colors = (count_colors >= 3 && count_colors <= 7) ? count_colors : m_count_colors;
}

void CSameGameBoard::set_cells_count(int32_t &count_cols)
{
	// Проверка на выход за границы
	m_cols = m_rows = sqrt(count_cols);
}

void CSameGameBoard::set_cells_size(int32_t &cells_size)
{
	m_width = m_height = cells_size;
}