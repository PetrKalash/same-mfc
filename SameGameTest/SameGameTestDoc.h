// SameGameTestDoc.h: интерфейс класса CSameGameTestDoc

#pragma once
#include "SameGameBoard.h"
#include <stack>

class CSameGameTestDoc : public CDocument
{
protected:
	CSameGameTestDoc() noexcept;
	DECLARE_DYNCREATE(CSameGameTestDoc)

// Атрибуты
public:

// Доступ к игровой доске
public:
	void delete_cells(int32_t row, int32_t col);
	void setup_board()									{ m_board->setup_board();				}
	void delete_board()									{ m_board->delete_board();				}
	bool is_game_over()									{ return m_board->is_game_over();		}

	COLORREF get_colors(int32_t row, int32_t col) const { return m_board->get_colors(row, col); }
	int32_t get_num_colors() const						{ return m_board->get_num_colors();	    }
	int32_t get_rows() const							{ return m_board->get_rows();		    }
	int32_t get_cols() const							{ return m_board->get_cols();		    }
	int32_t get_width()	const							{ return m_board->get_width();		    }
	int32_t get_height() const							{ return m_board->get_height();		    }
	int32_t get_count_cells() const						{ return m_board->get_count_cells();	}

	void set_count_colors(int32_t count_colors);
	void set_cells_count(int32_t count_cols)			{ m_board->set_cells_count(count_cols); }
	void set_cells_size(int32_t cells_size)				{ m_board->set_cells_size(cells_size);  }

	void redo_last();
	void undo_last();
	bool can_redo();
	bool can_udo();

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CSameGameTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Функции очистки стеков «Отмена/Повтор»
	void clear_redo();
	void clear_undo();

	// Экземпляр объекта игровой доски
	CSameGameBoard *m_board;

	std::stack<CSameGameBoard*> m_undo;	// отмена
	std::stack<CSameGameBoard*> m_redo; // повтор

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
