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
	// Получение цвета игровой ячейки
	COLORREF get_colors(int32_t row, int32_t col) { return m_board.get_colors(row, col); }
	// Получение кол-ва ячеек у строки
	int32_t get_rows() const					  { return m_board.get_rows(); }	
	// Получение кол-ва ячеек у столбца
	int32_t get_cols() const					  { return m_board.get_cols(); }
	// Получение ширины игрового поля
	int32_t get_width()  const					  { return m_board.get_width();  }	
	// Получение высоты игрового поля
	int32_t get_height() const					  { return m_board.get_height(); }

	// Очистка одинаковых ячеек
	void delete_cells()							  { m_board.delete_cells(); }

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
