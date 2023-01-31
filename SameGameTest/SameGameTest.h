
// SameGameTest.h: основной файл заголовка для приложения SameGameTest
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CSameGameTestApp:
// Сведения о реализации этого класса: SameGameTest.cpp
//

class CSameGameTestApp : public CWinApp
{
public:
	CSameGameTestApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSameGameTestApp theApp;
