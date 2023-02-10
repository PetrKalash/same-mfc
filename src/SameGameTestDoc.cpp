// SameGameTestDoc.cpp: реализация класса CSameGameTestDoc 
#include "pch.h"
#include "framework.h"

#ifndef SHARED_HANDLERS
#include "SameGameTest.h"
#endif

#include "SameGameTestDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSameGameTestDoc
IMPLEMENT_DYNCREATE(CSameGameTestDoc, CDocument)
BEGIN_MESSAGE_MAP(CSameGameTestDoc, CDocument)
END_MESSAGE_MAP()

// Создание или уничтожение CSameGameTestDoc
CSameGameTestDoc::CSameGameTestDoc() noexcept
{
	// Игровая доска
	m_board = new CSameGameBoard;
}

CSameGameTestDoc::~CSameGameTestDoc()
{
	// Удаляем текущую игровую доску
	delete m_board;
	// Удаляем всё из стека «Отмена» 
	clear_undo();
	// Удаляем всё из стека «Повтор»
	clear_redo();
}

void CSameGameTestDoc::delete_cells(int32_t row, int32_t col)
{
	// Сохранение текущего состояния доски в стеке «Отмена»
	m_undo.push(new CSameGameBoard(*m_board));

	// Очищаем стек «Повтор»
	clear_redo();

	// Затем удаляем блоки
	m_board->delete_cells(row, col);
	int32_t blocks = m_board->get_count_cells();

	// Очищаем стек «Отмена» в конце игры
	if(m_board->is_game_over()) clear_undo();

	// Возвращаем количество блоков
	//return blocks;
}

void CSameGameTestDoc::redo_last()
{
	// Смотрим, есть ли у нас что-нибудь в стеке «Повтор»
	if(m_redo.empty()) return;

	// Помещаем текущую игровую доску в стек «Отмена»
	m_undo.push(m_board);

	// Назначаем верхний элемент стека «Повтор» текущим
	m_board = m_redo.top();
	m_redo.pop();
}

void CSameGameTestDoc::undo_last()
{ 
	// Смотрим, есть ли у нас что-нибудь в стеке «Отмена»
	if(m_undo.empty()) return;

	// Помещаем текущую игровую доску в стек «Повтор»
	m_redo.push(m_board);

	// Назначаем верхний элемент стека «Отмена» текущим
	m_board = m_undo.top();
	m_undo.pop();
}

bool CSameGameTestDoc::can_redo()
{
	// Убеждаемся, сможем ли мы выполнить повтор действия (не пуст ли стек)
	return !m_redo.empty();
}

bool CSameGameTestDoc::can_undo()
{
	// Убеждаемся, что у нас есть возможность выполнить отмену действия
	return !m_undo.empty();
}

void CSameGameTestDoc::clear_redo()
{
	// Очищаем стек «Повтор»
	while(!m_redo.empty())
	{
		delete m_redo.top();
		m_redo.pop();
	}
}

void CSameGameTestDoc::clear_undo()
{
	// Очищаем стек «Отмена»
	while(!m_undo.empty())
	{
		delete m_undo.top();
		m_undo.pop();
	}
}

void CSameGameTestDoc::set_count_colors(int32_t count_colors)
{
	// Вызываем метод для изменения кол-ва цветов на поле
	m_board->set_count_colors(count_colors);
	// Присваиваем ячейкам новые значения на игровом поле
	m_board->setup_board();
}

BOOL CSameGameTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) return FALSE;
	
	this->SetTitle(L"Аркадная игра");

	// Повторная инициализация игровой доски
	m_board->setup_board();
	
	return TRUE;
}

// Сериализация CSameGameTestDoc
void CSameGameTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		
	}
	else
	{
		
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CSameGameTestDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CSameGameTestDoc::InitializeSearchContent()
{
	CString strSearchContent;
	SetSearchContent(strSearchContent);
}

void CSameGameTestDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CSameGameTestDoc
#ifdef _DEBUG
void CSameGameTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSameGameTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// Команды CSameGameTestDoc
