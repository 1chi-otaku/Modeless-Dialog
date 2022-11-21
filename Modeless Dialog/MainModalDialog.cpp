#include "MainModalDialog.h"
#include "CafeModalDialogHead.h"
#include "PetrolModalDialogHead.h"

CMainModalDialog* CMainModalDialog::ptr = NULL;

CMainModalDialog::CMainModalDialog(void)
{
	ptr = this;
}


void CMainModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CMainModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	
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
	if (id == IDC_BUTTON1 || id == IDC_BUTTON3) 
	{
		TCHAR buffer[200];
		int sum = 0;
		int total = 0;
		INT_PTR result;
		if (id == IDC_BUTTON1) {
			CafeModalDialog dlg;
			result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG4), hwnd, CafeModalDialog::DlgProc);
		}
		else {
			PetrolModalDialog dlg;
			result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, PetrolModalDialog::DlgProc);
		}
		if (result == IDOK) {
			GetWindowText(hEditCafe, buffer, 200);
			sum = _wtoi(buffer);
			GetWindowText(hEditPetrol, buffer, 200);
			total = sum + _wtoi(buffer);
			wsprintf(buffer, TEXT("%d"), total);
			SetWindowText(hEditTotal, buffer);
		}
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