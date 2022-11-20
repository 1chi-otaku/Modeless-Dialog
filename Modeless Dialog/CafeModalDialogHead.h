#pragma once
#include "header.h"

class CafeModalDialog
{
public:
	CafeModalDialog(void);
public:
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CafeModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hTotal;
	HWND hPrice[4];
	HWND hQua[4];
	HWND hCheckFood[4];
	TCHAR text[200];
};
