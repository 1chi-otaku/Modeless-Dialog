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

int CafeModalDialog::CalculateSum(HWND hwnd)		//Calculates the current sum according to the marked items
{
	TCHAR buffer[16];
	int sum = 0;
	int total = 0;
	for (int i = 0; i < 4; i++)
	{
		LRESULT lCheck = SendMessage(ptr->hCheckFood[i], BM_GETCHECK, 0, 0);
		if (lCheck == BST_CHECKED) {
			GetWindowText(ptr->hPrice[i], buffer, 200);
			sum = _wtoi(buffer);
			GetWindowText(ptr->hQua[i], buffer, 200);
			total += (sum * _wtoi(buffer));
		}
	}
	return total;
}


void CafeModalDialog::CheckActive(HWND hwnd)
{
	//Getting state of buttons.
	LRESULT lCheck1 = SendMessage(ptr->hCheckFood[0], BM_GETCHECK, 0, 0);
	LRESULT lCheck2 = SendMessage(ptr->hCheckFood[1], BM_GETCHECK, 0, 0);
	LRESULT lCheck3 = SendMessage(ptr->hCheckFood[2], BM_GETCHECK, 0, 0);
	LRESULT lCheck4 = SendMessage(ptr->hCheckFood[3], BM_GETCHECK, 0, 0);
	//Buttons state logic.
	if (lCheck1 == BST_CHECKED)
		EnableWindow(ptr->hQua[0], TRUE);
	else {
		EnableWindow(ptr->hQua[0], FALSE);
	}
	if (lCheck2 == BST_CHECKED)
		EnableWindow(ptr->hQua[1], TRUE);
	else {
		EnableWindow(ptr->hQua[1], FALSE);
	}
	if (lCheck3 == BST_CHECKED)
		EnableWindow(ptr->hQua[2], TRUE);
	else {
		EnableWindow(ptr->hQua[2], FALSE);
	}
	if (lCheck4 == BST_CHECKED)
		EnableWindow(ptr->hQua[3], TRUE);
	else {
		EnableWindow(ptr->hQua[3], FALSE);
	}
}

BOOL CafeModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	//Getting handles of Cafe Window.
	for (int i = 0; i < 4; i++) {
		hPrice[i] = GetDlgItem(hwnd, IDC_EDIT01 + i);
		hQua[i] = GetDlgItem(hwnd, IDC_EDIT05 + i);
	}
	for (int i = 0; i < 4; i++)
		hCheckFood[i] = GetDlgItem(hwnd, IDC_CHECK1 + i);
	hTotal = GetDlgItem(hwnd, IDC_EDIT5);
	//Setting default Edit Control values.
	SetWindowText(hPrice[0], TEXT("19"));
	SetWindowText(hPrice[1], TEXT("2"));
	SetWindowText(hPrice[2], TEXT("12"));
	SetWindowText(hPrice[3], TEXT("21"));
	SetWindowText(hQua[0], TEXT("0"));
	SetWindowText(hQua[1], TEXT("0"));
	SetWindowText(hQua[2], TEXT("0"));
	SetWindowText(hQua[3], TEXT("0"));
	SetWindowText(hTotal, TEXT("0"));
	//Disable Qua. Edit Control by default.
	EnableWindow(hQua[0], FALSE);
	EnableWindow(hQua[1], FALSE);
	EnableWindow(hQua[2], FALSE);
	EnableWindow(hQua[3], FALSE);	

	return TRUE;
}


void CafeModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	ptr->CheckActive(hwnd);													//Check state of buttons.

	if (id == IDC_BUTTON1) {												//If 'Calculate' button has been pressed:
		TCHAR buffer[16];
		int a = ptr->CalculateSum(hwnd);									//Calculates current sum.
		wsprintf(buffer, TEXT("%d"), a);
		SetWindowText(ptr->hTotal, buffer);		
	}
	
	if (id == IDOK) //If OKAY is pressed
	{
		TCHAR buffer[16];
		int total = CalculateSum(hwnd);
		wsprintf(buffer, TEXT("%d"), total);
		HWND hParent = GetParent(hwnd);										//Getting handle of parent window.
		HWND hMainFood = GetDlgItem(hParent, IDC_EDIT3);
		SetWindowText(hMainFood, buffer);									//Setting Total Edit Control value to the Cafe Edit Control of Parent window.

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