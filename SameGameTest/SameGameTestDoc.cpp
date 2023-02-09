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
}

CSameGameTestDoc::~CSameGameTestDoc()
{
}

void CSameGameTestDoc::set_count_colors(int32_t count_colors)
{
	// Вызываем метод для изменения кол-ва цветов на поле
	m_board.set_count_colors(count_colors);
	// Присваиваем ячейкам новые значения на игровом поле
	m_board.setup_board();
}

BOOL CSameGameTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) return FALSE;
	
	// Повторная инициализация игровой доски
	m_board.setup_board();
	
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
