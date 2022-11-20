#pragma once
#include "header.h"

class PetrolModalDialog
{
public:
	PetrolModalDialog(void);
public:
	~PetrolModalDialog(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static PetrolModalDialog* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND hStatic;
	static HWND hAddDialog; // дескриптор дополнительного диалога
};

