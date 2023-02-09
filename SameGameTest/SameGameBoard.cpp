#include "pch.h"
#include "SameGameBoard.h"
#include <random>

CSameGameBoard::CSameGameBoard() : m_cells{}, 
m_width{50}, m_height{50},
m_rows{15}, m_cols{15},
m_count_colors{3}, m_count_cells{}
{
	// Устанавливаем собственный цвет для каждой ячейки массива цветов
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
	// Если ячейки на игровом поле еще не сгенерированы, создаем новое поле
	create_cells();

	// Перебираемся по всем строкам и столбцам игрового поля
	for (size_t rows{}; rows < m_rows; ++rows)
		for (size_t cols{}; cols < m_cols; ++cols)
			// Устанавливаем значение случайного цвета блока (цвет фона не учитываем)
			m_cells.at(rows).at(cols) = 1 + std::mt19937(std::random_device {}())() % m_count_colors;

	// Ищем новое кол-во ячеек на игровом поле после его обновления
	m_count_cells = m_rows * m_cols;
}

void CSameGameBoard::create_cells()
{
	// Очистка игровой доски
	delete_board();
	// Выделение памяти под ячейки игровой доски
	m_cells.assign(m_rows, std::vector<int32_t>(m_cols));
}

bool CSameGameBoard::is_game_over()
{
	// Перебираемся по всем строкам и столбцам игрового поля (слева-направо снизу-вверх)
	for (int32_t cols{}; cols < m_cols; ++cols) {
		for (int32_t rows{m_rows-1}; rows >= 0; --rows) {
			// Если мы попали на ячейку с цветом фона, то это значит, что столбец уже уничтожен
			if (m_cells.at(rows).at(cols) == 0) break;

			// Проверка на выход за границы
			if (rows - 1 < 0 || cols + 1 > m_cols) continue;

			// Проверяем соседние ячейки сверху и справа. Возвращаем false, если хотя бы одна из них равна цвету соседней
			if (m_cells.at(rows - 1).at(cols) == m_cells.at(rows).at(cols) ||
				m_cells.at(rows).at(cols + 1) == m_cells.at(rows).at(cols)) return false;
		}
	}
	// Если же ячеек с одинаковыми соседними цветами нет, возвращаем true
	return true;
}

void CSameGameBoard::cells_move_down()
{
	bool flag = true;			// проверка на передвинутую строку
	// Заменяем пустые ячейки на поле заполненными до тех пор, пока не достигнем границы поля
	while (flag)
	{
		// Обнуляем значение флага после каждого нового прохода по игровому полю
		flag = false;
		// Cдвиг ячеек вниз - первую строку проверять не нужно, чтобы не выйти за границы
		for (size_t rows{1}; rows < m_rows; ++rows) {
			for (size_t cols{}; cols < m_cols; ++cols) {
				// Как только мы нашли на игровом поле пустые ячейки, начинаем заменять их на ячейки, что выше
				if (m_cells.at(rows).at(cols) == 0 && m_cells.at(rows - 1).at(cols) != 0) {
					// Производим замену и ставим 1 на флаг, т.к. мы нашли ячейку для сдвига
					std::swap(m_cells.at(rows - 1).at(cols), m_cells.at(rows).at(cols)); flag = true;
				}
			}
		}
	}
}

void CSameGameBoard::cells_move_left()
{
	int32_t last_cols{};		// передвинутые в конец строки
	bool flag = true;			// проверка на передвинутую строку
	while (flag)
	{
		flag = false; last_cols++;
		// Смещение ячеек влево - находим пустой столбец по всем строкам 
		// (у него должна быть гарантированно пустая первая ячейка)
		for (size_t cols {}; cols < m_cols; ++cols) {
			// Ищем пустую ячейку, начиная с самого верха игрового поля
			if (m_cells.at(0).at(cols) != 0) continue;

			// Если мы нашли такую ячейку, то смортим весь ее столбец
			for (size_t rows {}; rows < m_rows; ++rows) {
				// Если хотя бы одна из ячеек цветная, сразу же выходим из цикла и проверяем другой столбец
				if (m_cells.at(rows).at(cols) != 0) break;
				// Проверка, что у столбца все блоки пустые, и запрет уже передвинутых
				if (rows != m_rows - 1 || cols >= m_cols - last_cols) continue;

				// Если у строки все блоки пустые, начинаем замену
				for (size_t rows{}; rows < m_rows; ++rows) {
					// Меняем один столбец игрового поля с другим
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
	// Кол-во удаленных ячеек
	int32_t count_delete_cells{};

	// Узнаем цвет ячеек, которые нужно удалять (он будет равен выбранной ячейке)
	int32_t color_cells = m_cells.at(row).at(col);

	// Если цвет равен 0, значит мы нажали по пустой ячейке
	if (color_cells == 0) return;

	// Начинаем удалять ячейки одинакового цвета от центра выбранной ячейки
	delete_neighbor_cells(row - 1, col, color_cells, count_delete_cells);	// Вверх
	delete_neighbor_cells(row + 1, col, color_cells, count_delete_cells);	// Вниз
	delete_neighbor_cells(row, col - 1, color_cells, count_delete_cells);	// Влево
	delete_neighbor_cells(row, col + 1, color_cells, count_delete_cells);	// Вправо

	// После удаления всех ячеек сдвигаем остальные ячейки
	compact_board();

	// После всех проходов по ячейкам с одинаковым цветом ищем оставшееся кол-во блоков
	m_count_cells -= count_delete_cells;
}

void CSameGameBoard::delete_neighbor_cells(int32_t row, int32_t col, int32_t color, int32_t &count_delete_cells)
{
	// Проверка на выход за границы
	if (row < 0 || row >= m_rows || col < 0 || col >= m_cols) return;

	// Проверка на то, что цвет блока не совпадает с переданным
	if (m_cells.at(row).at(col) != color) return;

	// Увеличиваем кол-во каждой удаленной ячейки
	count_delete_cells++;

	// Если ячейка сверху равна цвету первой ячейки, удаляем верхнюю ячейку
	m_cells.at(row).at(col) = 0;

	// Делаем проход со всех сторон соседних ячеек
	delete_neighbor_cells(row - 1, col, color, count_delete_cells);    // Вверх
	delete_neighbor_cells(row + 1, col, color, count_delete_cells);    // Вниз
	delete_neighbor_cells(row, col - 1, color, count_delete_cells);	   // Влево
	delete_neighbor_cells(row, col + 1, color, count_delete_cells);    // Вправо
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

void CSameGameBoard::set_count_colors(int32_t &count_colors)
{
	// Устанавливаем на поле кол-во цветов, равное переданному кол-ву. Если мы 
	// выходим за игровые пределы, то возвращаем текущее кол-во цветов
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