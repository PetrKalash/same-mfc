// OptionDialog.cpp: файл реализации

#include "pch.h"
#include "SameGameTest.h"
#include "afxdialogex.h"
#include "OptionDialog.h"

// Диалоговое окно COptionDialog
IMPLEMENT_DYNAMIC(COptionDialog, CDialog)

COptionDialog::COptionDialog(bool bRowColumn, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_OPTIONS, pParent)
	, m_value(0)
    , m_bRowColumnDialog(bRowColumn)
{

}

COptionDialog::~COptionDialog()
{
}

void COptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT_1, m_static_text);
	DDX_Text(pDX, IDC_EDIT_VALUE_1, m_value);
}

BEGIN_MESSAGE_MAP(COptionDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULTS, &COptionDialog::OnBnClickedButtonDefaults)
    ON_BN_CLICKED(IDOK, &COptionDialog::OnBnClickedOk)
END_MESSAGE_MAP()

// Обработчики сообщений COptionDialog
void COptionDialog::OnBnClickedButtonDefaults()
{
    // Отдельно рассматриваем два варианта
    if(m_bRowColumnDialog) m_value = 55;    // размер ячеек
    else m_value = 200;                     // количество ячеек

    // Обновляем параметры элементов до новых значений
    UpdateData(false);
}

BOOL COptionDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    if(m_bRowColumnDialog)
    {
        // Сначала обновляем заголовок диалогового окна
        SetWindowText(_T("Изменение размера ячейки"));
        // Затем обновляем элементы «Static Text»
        m_static_text.SetWindowText(_T("Размер в px: "));
    }
    else
    {
        // Сначала обновляем заголовок диалогового окна
        SetWindowText(_T("Изменение количества ячеек"));
        // Затем обновляем элементы «Static Text»
        m_static_text.SetWindowText(_T("Кол-во в шт: "));
    }

    return TRUE;
}

void COptionDialog::OnBnClickedOk()
{
    CDialog::OnOK();
}