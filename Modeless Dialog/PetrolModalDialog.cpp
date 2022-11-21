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
	hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
	hRadio1 = GetDlgItem(hwnd, IDC_RADIO1);
	hRadio2 = GetDlgItem(hwnd, IDC_RADIO2);
	
	SendMessage(hComboBox, CB_ADDSTRING, 0, LPARAM(TEXT("P-98")));
	SendMessage(hComboBox, CB_ADDSTRING, 0, LPARAM(TEXT("P-95")));
	SendMessage(hComboBox, CB_ADDSTRING, 0, LPARAM(TEXT("P-91")));

	EnableWindow(hEditQua, FALSE);
	EnableWindow(hEditSum, FALSE);

	SetWindowText(hEditPrice, TEXT("0"));
	SetWindowText(hEditQua, TEXT("0"));
	SetWindowText(hEditSum, TEXT("0"));
	SetWindowText(hEditTotal, TEXT("0"));

	
	return TRUE;
}


void PetrolModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	int indexCombo = SendMessage(ptr->hComboBox, CB_GETCURSEL, 0, 0);
	if (codeNotify == EN_UPDATE && id == IDC_EDIT4 && indexCombo >= 0) {
		TCHAR buffer[16];
		TCHAR buffer2[16];
		GetWindowText(hEditSum, buffer, 16);
		int Sum = _wtoi(buffer);
		wsprintf(buffer, TEXT("%d"), Sum);
		SetWindowText(hEditTotal, buffer);
	}
	if (codeNotify == EN_UPDATE && id == IDC_EDIT3) {

		TCHAR buffer[16];
		GetWindowText(hEditQua, buffer, 16);
		int Qua = _wtoi(buffer);
		GetWindowText(hEditPrice, buffer, 16);
		int Price = _wtoi(buffer);
		int Sum = Qua * Price;
		wsprintf(buffer, TEXT("%d"), Sum);

		SetWindowText(hEditSum, buffer);
		SetWindowText(hEditTotal, buffer);
	}
	
	

	

	if (id == IDC_COMBO1 && codeNotify == CBN_SELCHANGE)
	{
		
		switch (indexCombo)
		{
		case 0:
			SetWindowText(hEditPrice, TEXT("11"));
			break;
		case 1:
			SetWindowText(hEditPrice, TEXT("13"));
			break;
		case 2:
			SetWindowText(hEditPrice, TEXT("19"));
			break;
		}
	}

	LRESULT lCheck1 = SendMessage(hRadio1, BM_GETCHECK, 0, 0);
	LRESULT lCheck2 = SendMessage(hRadio2, BM_GETCHECK, 0, 0);

	if (lCheck1 == BST_CHECKED) {
		EnableWindow(hEditQua, TRUE);
		EnableWindow(hEditSum, FALSE);
	}
	if (lCheck2 == BST_CHECKED){
		EnableWindow(hEditSum, TRUE);
		EnableWindow(hEditQua, FALSE);
	}
	

	if (id == IDOK)
	{
		int total = 0;
		TCHAR buffer[16];
		GetWindowText(hEditTotal, buffer, 16);
		HWND hParent = GetParent(hwnd);
		HWND hMainPetrol = GetDlgItem(hParent, IDC_EDIT1);
		SetWindowText(hMainPetrol, buffer);
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