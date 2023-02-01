// SameGameTestDoc.h: интерфейс класса CSameGameTestDoc

#pragma once
#include "SameGameBoard.h"

class CSameGameTestDoc : public CDocument
{
protected:
	CSameGameTestDoc() noexcept;
	DECLARE_DYNCREATE(CSameGameTestDoc)

// Атрибуты
public:

// Операции
public:
	void delete_cells()									{ m_board.delete_cells(); }

	COLORREF get_colors(int32_t row, int32_t col) const { return m_board.get_colors(row, col); }
	int32_t get_rows() const							{ return m_board.get_rows(); }	
	int32_t get_cols() const							{ return m_board.get_cols(); }
	int32_t get_width()	const							{ return m_board.get_width(); }	
	int32_t get_height() const							{ return m_board.get_height(); }
	int32_t get_num_colors() const						{ return m_board.get_num_colors(); }

	// Установка нового кол-ва цветов для ячеек на игровом поле
	void set_num_colors(int32_t count_colors);

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
	// Экземпляр объекта игровой доски
	CSameGameBoard m_board;

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
