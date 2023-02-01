// SameGameTestView.cpp: реализация класса CSameGameTestView
#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "SameGameTest.h"
#endif

#include "SameGameTestDoc.h"
#include "SameGameTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSameGameTestView
IMPLEMENT_DYNCREATE(CSameGameTestView, CView)
BEGIN_MESSAGE_MAP(CSameGameTestView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение CSameGameTestView
CSameGameTestView::CSameGameTestView() noexcept
{
}

CSameGameTestView::~CSameGameTestView()
{
}

BOOL CSameGameTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// Рисование CSameGameTestView
void CSameGameTestView::OnDraw(CDC* pDC)
{
	// Создание указателя на документ, чтобы получить данные игрового поля
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	// Получение координат рабочей области окна у пользователя
	CRect rect_client; GetClientRect(rect_client);

	// Устанавливаем черный цвет заднему фону
	COLORREF color = pDoc->get_colors(-1, -1);
	// Отрисовываем задний фон
	pDC->FillSolidRect(rect_client, color);

	// Создаем кисть для рисования цветных блоков
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);

	int32_t indent_cells {5};

	// Заполнение игрового поля ячейками
	for (size_t count_rows{}, row{}; row < pDoc->get_rows(); ++row, count_rows += indent_cells) {
		for (size_t count_cols{}, col{}; col < pDoc->get_cols(); ++col, count_cols += indent_cells) {
			
			// Устанавливаем для ячейки случайный цвет на игровом поле (который уже сгенерирован)
			color = pDoc->get_colors(row, col);

			// Работа с ячейками на поле
			CRect rcBlock;

			// Позиция одной ячейки
			rcBlock.top = row * pDoc->get_height() + count_rows;
			rcBlock.left = col * pDoc->get_width() + count_cols;

			// Размер одной ячейки
			rcBlock.right = rcBlock.left + pDoc->get_width();
			rcBlock.bottom = rcBlock.top + pDoc->get_height();

			// Заполняем блок соответствующим цветом
			pDC->FillSolidRect(rcBlock, color);
			pDC->Rectangle(rcBlock);
		}
	}
}

// Диагностика CSameGameTestView
#ifdef _DEBUG
void CSameGameTestView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSameGameTestDoc* CSameGameTestView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameTestDoc)));
	return (CSameGameTestDoc*)m_pDocument;
}
#endif //_DEBUG

// Обработчики сообщений CSameGameTestView
void CSameGameTestView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// Изменяем размеры окна
	ResizeWindow();
}

void CSameGameTestView::ResizeWindow()
{
	int32_t indent_cells {5};

	// Создание указателя на документ, чтобы получить данные игрового поля
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	// Получение координат рабочей области окна у пользователя
	CRect rect_client;	GetClientRect(rect_client);
	// Получение размера всего окна
	CRect rect_window;	GetParentFrame()->GetWindowRect(rect_window);

	// Вычисляем произведение кол-ва ячеек у строки и умножаем на их размер
	int32_t width_ciles = pDoc->get_width() * pDoc->get_cols();
	int32_t height_ciles = pDoc->get_height() * pDoc->get_rows();

	// Вычисление разницы между значениями двух областей дает площадь 
	// пространства, используемого строкой заголовка, меню и границами окна
	int32_t width_menu_bar = rect_window.Width() - rect_client.Width();
	int32_t height_menu_bar = rect_window.Height() - rect_client.Height();

	// Вычисляем размер границы между блоками
	int32_t width_indent = indent_cells * pDoc->get_cols() - indent_cells;
	int32_t height_indent = indent_cells * pDoc->get_cols() - indent_cells;

	// Изменяем размеры окна, исходя из размеров нашей доски
	rect_window.right = rect_window.left + width_ciles + width_menu_bar + width_indent;
	rect_window.bottom = rect_window.top + height_ciles + height_menu_bar + height_indent;

	// Функция MoveWindow() изменяет размер окна фрейма
	GetParentFrame()->MoveWindow(rect_window);
}

void CSameGameTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Создание указателя на документ, чтобы получить данные игрового поля
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	// Получаем координаты мыши
	int32_t point_x = point.x / pDoc->get_width();
	int32_t point_y = point.y / pDoc->get_width();

	// Очистка ячеек на игровом поле
	pDoc->delete_cells();

	// Перерисовка View после изменения игрового поля
	Invalidate();
	UpdateWindow();

	// Сообщение об окончании игры
	CString finish_game(_T("No more moves left"));
	MessageBox(finish_game, _T("Finish Game!"), MB_OK | MB_ICONMASK);
	
	// OnLButtonDown по умолчанию
	CView::OnLButtonDown(nFlags, point);
}
