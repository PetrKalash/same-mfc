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
	// 
	void set_color_count(int32_t count_colors);

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

	// Изменение уровня сложности
	afx_msg void OnLevelEasy();
	afx_msg void OnLevelNormal();
	afx_msg void OnLevelHard();
	afx_msg void OnLevelCrazy();
	afx_msg void OnLevelImpossible();

	// Обновление меню
	afx_msg void OnUpdateLevelEasy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevelNormal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevelHard(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevelCrazy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevelImpossible(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // версия отладки в SameGameTestView.cpp
inline CSameGameTestDoc* CSameGameTestView::GetDocument() const
   { return reinterpret_cast<CSameGameTestDoc*>(m_pDocument); }
#endif

