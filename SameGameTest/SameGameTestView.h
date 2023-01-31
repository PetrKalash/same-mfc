// SameGameTestView.h: интерфейс класса CSameGameTestView

#pragma once
class CSameGameTestView : public CView
{
protected: // создать только из сериализации
	CSameGameTestView() noexcept;
	DECLARE_DYNCREATE(CSameGameTestView)

// Атрибуты
public:
	CSameGameTestDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CSameGameTestView();
	void ResizeWindow();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // версия отладки в SameGameTestView.cpp
inline CSameGameTestDoc* CSameGameTestView::GetDocument() const
   { return reinterpret_cast<CSameGameTestDoc*>(m_pDocument); }
#endif

