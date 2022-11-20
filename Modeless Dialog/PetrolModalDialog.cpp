#include "PetrolModalDialogHead.h"

PetrolModalDialog* PetrolModalDialog::ptr = NULL;

PetrolModalDialog::PetrolModalDialog(void)
{
	ptr = this;
}


void PetrolModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL PetrolModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hEditPrice = GetDlgItem(hwnd, IDC_EDIT2);
	hEditQua = GetDlgItem(hwnd, IDC_EDIT3);
	hEditSum = GetDlgItem(hwnd, IDC_EDIT4);
	hEditTotal = GetDlgItem(hwnd, IDC_EDIT5);
	
	SetWindowText(hEditPrice, TEXT("0"));
	SetWindowText(hEditQua, TEXT("0"));
	SetWindowText(hEditSum, TEXT("0"));
	SetWindowText(hEditTotal, TEXT("0"));

	
	return TRUE;
}


void PetrolModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDOK)
	{
		EndDialog(hwnd, IDOK);
	}
	else if (id == IDCANCEL)
	{
		EndDialog(hwnd, IDCANCEL);
	}
}

BOOL CALLBACK PetrolModalDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}