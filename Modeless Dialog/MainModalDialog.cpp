#include "MainModalDialog.h"
#include "CafeModalDialogHead.h"

CMainModalDialog* CMainModalDialog::ptr = NULL;

CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
}

CMainModalDialog::~CMainModalDialog(void)
{

}

void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hButtonCafe = GetDlgItem(hwnd, IDC_BUTTON1);
	hButtonPetrol = GetDlgItem(hwnd, IDC_BUTTON3);
	hButtonProceed = GetDlgItem(hwnd, IDC_BUTTON4);
	
	hEditPetrol = GetDlgItem(hwnd, IDC_EDIT1);
	hEditCafe = GetDlgItem(hwnd, IDC_EDIT3);
	hEditTotal = GetDlgItem(hwnd, IDC_EDIT4);
	SetWindowText(hEditPetrol, TEXT("0"));
	SetWindowText(hEditCafe, TEXT("0"));
	SetWindowText(hEditTotal, TEXT("0"));

	return TRUE;
}


void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BUTTON1)
	{
		// Проверим, открыто ли дополнительное немодальное окно
		if (CafeModalDialog::hAddDialog)
		{
			//Активизируем дополнительное немодальное окно
			SetForegroundWindow(CafeModalDialog::hAddDialog);
			return;
		}
		CafeModalDialog dlg;
		// Создаем немодальное диалоговое окно
		CafeModalDialog::hAddDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, CafeModalDialog::DlgProc);
		// Отображаем окно	
		ShowWindow(CafeModalDialog::hAddDialog, SW_RESTORE);
		TCHAR buffer[200];
		// Получаем текст с текстового поля ввода
		//GetWindowText(hEdit1, buffer, 200);
		// Отображаем текст на статике дополнительного диалога
		SetWindowText(dlg.hStatic, buffer);
	}
}

BOOL CALLBACK CMainModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}