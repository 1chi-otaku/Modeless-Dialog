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
	//Getting handles for Petrol window.
	hEditPrice = GetDlgItem(hwnd, IDC_EDIT2);
	hEditQua = GetDlgItem(hwnd, IDC_EDIT3);
	hEditSum = GetDlgItem(hwnd, IDC_EDIT4);
	hEditTotal = GetDlgItem(hwnd, IDC_EDIT5);
	hComboBox = GetDlgItem(hwnd, IDC_COMBO1);
	hRadio1 = GetDlgItem(hwnd, IDC_RADIO1);
	hRadio2 = GetDlgItem(hwnd, IDC_RADIO2);
	
	//Adding strings that contain fuel name to combobox.
	SendMessage(hComboBox, CB_ADDSTRING, 0, LPARAM(TEXT("P-98")));
	SendMessage(hComboBox, CB_ADDSTRING, 0, LPARAM(TEXT("P-95")));
	SendMessage(hComboBox, CB_ADDSTRING, 0, LPARAM(TEXT("P-91")));

	//Disable Qua. and Sum Edit Control by default.
	EnableWindow(hEditQua, FALSE);
	EnableWindow(hEditSum, FALSE);

	//Setting Edit Control values to 0 by default.
	SetWindowText(hEditPrice, TEXT("0"));
	SetWindowText(hEditQua, TEXT("0"));
	SetWindowText(hEditSum, TEXT("0"));
	SetWindowText(hEditTotal, TEXT("0"));

	return TRUE;
}


void PetrolModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	int indexCombo = SendMessage(ptr->hComboBox, CB_GETCURSEL, 0, 0);						//Getting the position of the current element in the combo box.
	if (codeNotify == EN_UPDATE && id == IDC_EDIT4 && indexCombo >= 0) {					//If there is at least one element in the combo box and Sum Edit Control was changed:
		TCHAR buffer[16];
		GetWindowText(hEditSum, buffer, 16);												//Getting Sum from Edit Control.												
		SetWindowText(hEditTotal, buffer);													//Setting it to the Total Sum.
	}
	if (codeNotify == EN_UPDATE && id == IDC_EDIT3) {										//If Qua. Edit control was changed.
		TCHAR buffer[16];
		GetWindowText(hEditQua, buffer, 16);												//Getting Qua. from Edit Control.
		int Qua = _wtoi(buffer);														//Convetring it to int.
		GetWindowText(hEditPrice, buffer, 16);												//Getting Price of the current fuel.
		int Price = _wtoi(buffer);													//Converting it to int.
		int Sum = Qua * Price;																
		wsprintf(buffer, TEXT("%d"), Sum);													

		SetWindowText(hEditSum, buffer);													//Setting Sum Edit Control according to selected qua.
		SetWindowText(hEditTotal, buffer);													//Setting Total sum with the same value.
	}
	
	if (id == IDC_COMBO1 && codeNotify == CBN_SELCHANGE)									//If item in Combo Box was changed.
	{
		switch (indexCombo)																	//Setting price to Price Edit Control according to the selected fuel.
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
	//Getting state of radio buttons.
	LRESULT lCheck1 = SendMessage(hRadio1, BM_GETCHECK, 0, 0);
	LRESULT lCheck2 = SendMessage(hRadio2, BM_GETCHECK, 0, 0);
	//Radio buttons activation logic.
	if (lCheck1 == BST_CHECKED) {
		EnableWindow(hEditQua, TRUE);
		EnableWindow(hEditSum, FALSE);
	}
	if (lCheck2 == BST_CHECKED){
		EnableWindow(hEditSum, TRUE);
		EnableWindow(hEditQua, FALSE);
	}
	
	if (id == IDOK)	//If OK has been pressed:
	{
		int total = 0;
		TCHAR buffer[16];
		GetWindowText(hEditTotal, buffer, 16);
		HWND hParent = GetParent(hwnd);									//Getting handle of parent window.
		HWND hMainPetrol = GetDlgItem(hParent, IDC_EDIT1);
		SetWindowText(hMainPetrol, buffer);								//Setting Total Edit Control value to the Petrol Edit Control of Parent window.
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