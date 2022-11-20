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

	for (int i = 0; i < 4; i++)
		hCheckFood[i] = GetDlgItem(hwnd, IDC_CHECK1 + i);


	
	SetWindowText(hPriceAndQua[0], TEXT("19.99"));
	SetWindowText(hPriceAndQua[1], TEXT("1.99"));
	SetWindowText(hPriceAndQua[2], TEXT("12.99"));
	SetWindowText(hPriceAndQua[3], TEXT("21.99"));
	EnableWindow(hPriceAndQua[4], FALSE);
	EnableWindow(hPriceAndQua[5], FALSE);
	EnableWindow(hPriceAndQua[6], FALSE);
	EnableWindow(hPriceAndQua[7], FALSE);

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
	LRESULT lCheck1 = SendMessage(ptr->hCheckFood[0], BM_GETCHECK, 0, 0);
	LRESULT lCheck2 = SendMessage(ptr->hCheckFood[1], BM_GETCHECK, 0, 0);
	LRESULT lCheck3 = SendMessage(ptr->hCheckFood[2], BM_GETCHECK, 0, 0);
	LRESULT lCheck4 = SendMessage(ptr->hCheckFood[3], BM_GETCHECK, 0, 0);
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	
	if (lCheck1 == BST_CHECKED)
		EnableWindow(ptr->hPriceAndQua[4], TRUE);
	else
		EnableWindow(ptr->hPriceAndQua[4], FALSE);

	if (lCheck2 == BST_CHECKED)
		EnableWindow(ptr->hPriceAndQua[5], TRUE);
	else
		EnableWindow(ptr->hPriceAndQua[5], FALSE);

	if (lCheck3 == BST_CHECKED)
		EnableWindow(ptr->hPriceAndQua[6], TRUE);
	else
		EnableWindow(ptr->hPriceAndQua[6], FALSE);

	if (lCheck4 == BST_CHECKED)
		EnableWindow(ptr->hPriceAndQua[7], TRUE);
	else
		EnableWindow(ptr->hPriceAndQua[7], FALSE);

	return FALSE;
}