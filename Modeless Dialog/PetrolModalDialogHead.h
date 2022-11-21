#pragma once
#include "header.h"

class PetrolModalDialog
{
public:
	PetrolModalDialog(void);
public:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static PetrolModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hStatic;
	TCHAR text[200];
	HWND hEditTotal, hEditSum, hEditQua, hEditPrice;
	HWND hRadio1, hRadio2;
	HWND hComboBox;

};

