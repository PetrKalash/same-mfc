// AboutDialog.cpp: файл реализации
//

#include "pch.h"
#include "SameGameTest.h"
#include "afxdialogex.h"
#include "AboutDialog.h"


// Диалоговое окно CAboutDialog

IMPLEMENT_DYNAMIC(CAboutDialog, CDialog)

CAboutDialog::CAboutDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ABOUTBOX, pParent)
{

}

CAboutDialog::~CAboutDialog()
{
}

void CAboutDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDialog, CDialog)
END_MESSAGE_MAP()


// Обработчики сообщений CAboutDialog
