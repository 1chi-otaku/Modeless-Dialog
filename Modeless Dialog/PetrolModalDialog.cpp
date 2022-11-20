#include "PetrolModalDialogHead.h"

PetrolModalDialog* PetrolModalDialog::ptr = NULL;
HWND PetrolModalDialog::hAddDialog = NULL;

PetrolModalDialog::PetrolModalDialog(void)
{
	ptr = this;
}

PetrolModalDialog::~PetrolModalDialog(void)
{

}

void PetrolModalDialog::Cls_OnClose(HWND hwnd)
{
	// Разрушаем немодальное диалоговое окно
	DestroyWindow(hwnd);
	hAddDialog = NULL;
}

BOOL PetrolModalDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	
	return TRUE;
}


void PetrolModalDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if (id == IDOK)
	{
		
	}
	else if (id == IDCANCEL)
	{
		// Разрушаем немодальное диалоговое окно
		DestroyWindow(hwnd);
		hAddDialog = NULL;
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