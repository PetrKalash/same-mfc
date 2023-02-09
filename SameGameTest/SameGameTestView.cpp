// SameGameTestView.cpp: реализация класса CSameGameTestView
#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "SameGameTest.h"
#endif

#include "SameGameTestDoc.h"
#include "SameGameTestView.h"
#include "OptionDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSameGameTestView
IMPLEMENT_DYNCREATE(CSameGameTestView, CView)
BEGIN_MESSAGE_MAP(CSameGameTestView, CView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LEVEL_EASY, &CSameGameTestView::OnLevelEasy)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_EASY, &CSameGameTestView::OnUpdateLevelEasy)
	ON_COMMAND(ID_LEVEL_CRAZY, &CSameGameTestView::OnLevelCrazy)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_CRAZY, &CSameGameTestView::OnUpdateLevelCrazy)
	ON_COMMAND(ID_LEVEL_HARD, &CSameGameTestView::OnLevelHard)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_HARD, &CSameGameTestView::OnUpdateLevelHard)
	ON_COMMAND(ID_LEVEL_IMPOSSIBLE, &CSameGameTestView::OnLevelImpossible)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_IMPOSSIBLE, &CSameGameTestView::OnUpdateLevelImpossible)
	ON_COMMAND(ID_LEVEL_NORMAL, &CSameGameTestView::OnLevelNormal)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_NORMAL, &CSameGameTestView::OnUpdateLevelNormal)
	ON_COMMAND(ID_SIZE_BLOCK, &CSameGameTestView::OnSizeBlock)
	ON_COMMAND(ID_COUNT_BLOCK, &CSameGameTestView::OnCountBlock)
	ON_COMMAND(ID_EDIT_UNDO, &CSameGameTestView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CSameGameTestView::OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, &CSameGameTestView::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CSameGameTestView::OnUpdateEditRedo)
	ON_COMMAND(ID_ABOUT_GAME, &CSameGameTestView::OnAboutGame)
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

	// Заполнение игрового поля ячейками
	for (int32_t row{}; row < pDoc->get_rows(); ++row) {
		for (int32_t col{}; col < pDoc->get_cols(); ++col) {
			
			// Устанавливаем для ячейки случайный цвет на игровом поле (который уже сгенерирован)
			color = pDoc->get_colors(row, col);

			// Работа с ячейками на поле
			CRect rcBlock;

			// Позиция одной ячейки
			rcBlock.top = row * pDoc->get_height();
			rcBlock.left = col * pDoc->get_width();

			// Размер одной ячейки
			rcBlock.right = rcBlock.left + pDoc->get_width();
			rcBlock.bottom = rcBlock.top + pDoc->get_height();

			// Заполняем блок соответствующим цветом
			pDC->FillSolidRect(&rcBlock, color);
			// Устанавливаем рамки для всех, кроме белых блоков (задний фон)
			if(color != RGB(255, 255, 255)) pDC->Rectangle(&rcBlock);
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

	// Изменяем размеры окна, исходя из размеров нашей доски
	rect_window.right = rect_window.left + width_ciles + width_menu_bar;
	rect_window.bottom = rect_window.top + height_ciles + height_menu_bar;

	// Функция MoveWindow() изменяет размер окна фрейма
	GetParentFrame()->MoveWindow(rect_window);
}

void CSameGameTestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Создание указателя на документ, чтобы получить данные игрового поля
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	// Получаем координаты мыши
	int32_t row = point.y / pDoc->get_height();
	int32_t col = point.x / pDoc->get_width();

	// Смотрим кол-во ячеек на игровом поле
	int32_t count_cells = pDoc->get_count_cells();

	// Очистка ячеек на игровом поле
	pDoc->delete_cells(row, col);

	// Смотрим кол-во ячеек после вызова удаления ячеек
	int32_t delete_count_cells = pDoc->get_count_cells();

	// Если кол-во яччек до равно кол-ву после удаления, значит на игровом поле изменений не произошло
	if (count_cells == delete_count_cells) return;

	// Перерисовка View после изменения игрового поля
	Invalidate();
	UpdateWindow();
	
	// Как только комбинаций для удаления не осталось, выводим сообщение об окончании игры
	if (pDoc->is_game_over())
	{
		CString finish_game;
		finish_game.Format(_T("Game Over! Blocks remaining: %d"), delete_count_cells);
		MessageBox(finish_game, _T("Finish Game!"), MB_OK | MB_ICONMASK);
	}
	
	// OnLButtonDown по умолчанию
	CView::OnLButtonDown(nFlags, point);
}

void CSameGameTestView::set_color_count(int32_t count_colors)
{
	// Создание указателя на документ, чтобы получить данные игрового поля
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	pDoc->set_count_colors(count_colors);

	// Перерисовывание игрового поля View
	Invalidate();
	UpdateWindow();
}

void CSameGameTestView::OnLevelEasy()
{
	// Устанавливаем кол-во цветов на поле
	set_color_count(3);
}

void CSameGameTestView::OnUpdateLevelEasy(CCmdUI *pCmdUI)
{
	// Создание указателя на документ, чтобы получить данные игрового поля
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	// Проверка установленного уровня сложности
	pCmdUI->SetCheck(pDoc->get_num_colors() == 3);
}

void CSameGameTestView::OnLevelNormal()
{
	set_color_count(4);
}

void CSameGameTestView::OnUpdateLevelNormal(CCmdUI *pCmdUI)
{
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	pCmdUI->SetCheck(pDoc->get_num_colors() == 4);
}

void CSameGameTestView::OnLevelHard()
{
	set_color_count(5);
}

void CSameGameTestView::OnUpdateLevelHard(CCmdUI *pCmdUI)
{
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	pCmdUI->SetCheck(pDoc->get_num_colors() == 5);
}

void CSameGameTestView::OnLevelCrazy()
{
	set_color_count(6);
}

void CSameGameTestView::OnUpdateLevelCrazy(CCmdUI *pCmdUI)
{
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	pCmdUI->SetCheck(pDoc->get_num_colors() == 6);
}

void CSameGameTestView::OnLevelImpossible()
{
	set_color_count(7);
}

void CSameGameTestView::OnUpdateLevelImpossible(CCmdUI *pCmdUI)
{
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	pCmdUI->SetCheck(pDoc->get_num_colors() == 7);
}

// Изменение количества блоков на игровом поле
void CSameGameTestView::OnCountBlock()
{
	// Получение указателя на документ для доступа к данным
	CSameGameTestDoc *pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	// Передаем 0 - изменяем количество блоков на игровом поле
	COptionDialog count_dialog(false, this);

	count_dialog.m_value = pDoc->get_rows() * pDoc->get_cols();

	// Начало работы с окном через форму
	if (count_dialog.DoModal() == IDOK)
	{
		// Проверка на корректность введенных границ
		int32_t min_value{90}, max_value{350};
		if (count_dialog.m_value < min_value || count_dialog.m_value > max_value)
		{
			CString message;
			message.Format(_T("The value size schould between %d and %d!"), min_value, max_value);
			MessageBox(message, _T("Error!"), MB_OK | MB_ICONERROR); return;
		}

		// Удаляем все ячейки на игровом поле
		pDoc->delete_board();
		// Изменям кол-во блоков на игровом поле на переданное кол-во в форме
		pDoc->set_cells_count(count_dialog.m_value);
		// Заново генерируем все игровое поле
		pDoc->setup_board();

		// Изменяем размеры окна
		ResizeWindow();
	}
}

// Изменение размера блоков через игровое поле
void CSameGameTestView::OnSizeBlock()
{
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc); if (!pDoc) return;

	// Создаем диалоговое окно
	COptionDialog size_dialog(true, this);

	size_dialog.m_value = pDoc->get_width();

	// Отображаем полученное окно
	if (size_dialog.DoModal() == IDOK)
	{
		// Проверка на корректность введенных границ
		int32_t min_value{50}, max_value{60};
		if (size_dialog.m_value < min_value || size_dialog.m_value > max_value)
		{
			CString message;
			message.Format(_T("The value size schould between %d and %d!"), min_value, max_value);
			MessageBox(message, _T("Error!"), MB_OK | MB_ICONERROR); return;
		}

		// Сначала удаляем игровое поле
		pDoc->delete_board();
		// Устанавливаем значения, переданные пользователем
		pDoc->set_cells_size(size_dialog.m_value);
		// Обновляем игровое поле
		pDoc->setup_board();

		// Изменяем размеры View
		ResizeWindow();
	}
}

void CSameGameTestView::OnEditUndo()
{
	// Получаем указатель на Document
	CSameGameTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc)
		return;
	pDoc->UndoLast();

	// Перерисовываем View
	Invalidate();
	UpdateWindow();
}

void CSameGameTestView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	
}

void CSameGameTestView::OnEditRedo()
{
	
}

void CSameGameTestView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	
}

void CSameGameTestView::OnAboutGame()
{

}