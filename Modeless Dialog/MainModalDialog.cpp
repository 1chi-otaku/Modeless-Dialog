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
	//Getting handles for EditControl objects
	hEditPetrol = GetDlgItem(hwnd, IDC_EDIT1);
	hEditCafe = GetDlgItem(hwnd, IDC_EDIT3);
	hEditTotal = GetDlgItem(hwnd, IDC_EDIT4);
	//Settings Edit controls object with 0 by default.
	SetWindowText(hEditPetrol, TEXT("0"));
	SetWindowText(hEditCafe, TEXT("0"));
	SetWindowText(hEditTotal, TEXT("0"));

	return TRUE;
}

void CMainModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDC_BUTTON1 || id == IDC_BUTTON3) //If Petrol or Cafe buttons are pressed.
	{
		INT_PTR result;																								
		TCHAR buffer[200];
		int sum = 0;
		int total = 0;
		if (id == IDC_BUTTON1) {	//If Cafe button pressed
			CafeModalDialog dlg;
			result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG4), hwnd, CafeModalDialog::DlgProc);				//Creates a Cafe window.
		}
		else {						//If Petrol button pressed
			PetrolModalDialog dlg;
			result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwnd, PetrolModalDialog::DlgProc);				//Creates a Petrol window.
		}
		if (result == IDOK) { //If OKAY is pressed
			GetWindowText(hEditCafe, buffer, 200);					//Getting Cafe sum.
			sum = _wtoi(buffer);
			GetWindowText(hEditPetrol, buffer, 200);				
			total = sum + _wtoi(buffer);						//Getting Petrol sum and add it to cafe sum.
			wsprintf(buffer, TEXT("%d"), total);
			SetWindowText(hEditTotal, buffer);						//Writes the result to 'Total' Edit control.
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