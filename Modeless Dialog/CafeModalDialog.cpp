#include "CafeModalDialogHead.h"

CafeModalDialog* CafeModalDialog::ptr = NULL;

CafeModalDialog::CafeModalDialog(void)
{
	ptr = this;
}


void CafeModalDialog::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL CafeModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hTotal = GetDlgItem(hwnd, IDC_EDIT5);
	for (int i = 0; i < 8; i++)
		hPriceAndQua[i] = GetDlgItem(hwnd, IDC_EDIT01+i);

	
	SetWindowText(hPriceAndQua[0], TEXT("19.99"));
	SetWindowText(hPriceAndQua[1], TEXT("1.99"));
	SetWindowText(hPriceAndQua[2], TEXT("12.99"));
	SetWindowText(hPriceAndQua[3], TEXT("21.99"));

	SetWindowText(hTotal, TEXT("0"));

	return TRUE;
}


void CafeModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
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