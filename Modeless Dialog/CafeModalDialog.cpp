#include "CafeModalDialogHead.h"

CafeModalDialog* CafeModalDialog::ptr = NULL;
HWND CafeModalDialog::hAddDialog = NULL;

CafeModalDialog::CafeModalDialog(void)
{
	ptr = this;
}

CafeModalDialog::~CafeModalDialog(void)
{

}

void CafeModalDialog::Cls_OnClose(HWND hwnd)
{
	// Разрушаем немодальное диалоговое окно
	DestroyWindow(hwnd);
	hAddDialog = NULL;
}

BOOL CafeModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hStatic = GetDlgItem(hwnd, IDC_STATIC1);
	SetWindowText(hwnd, TEXT("Дополнительный немодальный диалог"));
	SetWindowText(GetDlgItem(hwnd, IDC_EDIT1), TEXT("Передача данных главному диалогу!"));
	return TRUE;
}


void CafeModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDOK)
	{
		TCHAR buffer[200];
		// Получаем текст с текстового поля ввода
		GetWindowText(GetDlgItem(hwnd, IDC_EDIT1), buffer, 200);
		// Получаем дескриптор родительского (главного) окна
		HWND hParent = GetParent(hwnd);
		// Получаем дескриптор статика главного диалога
		HWND hStatic = GetDlgItem(hParent, IDC_STATIC1);
		// Отображаем текст на статике главного диалога
		SetWindowText(hStatic, buffer);
	}
	else if (id == IDCANCEL)
	{
		// Разрушаем немодальное диалоговое окно
		DestroyWindow(hwnd);
		hAddDialog = NULL;
	}
}

BOOL CALLBACK CafeModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}