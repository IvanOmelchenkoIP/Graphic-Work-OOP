#include "framework.h"

#include <vector>
#include <string>

#include "single_func_container.h"
#include "dlg_func_table.h"
#include "dlg_msg_processor.h"

#include "resource1.h"
#include "dlg_function_win.h"

static HWND hwndMain;
//**************************
//global intitializers
//-------------------------
static DlgMsgProcessor dmProcessor;

static BOOL CALLBACK DlgFunction(HWND, UINT, WPARAM, LPARAM);
//-------------------------
//****************************


//*************************
//-------------------------
// Function dialog class methods
//-------------------------
void FunctionDialog::InitDlg(HWND hWnd, HINSTANCE hInst)
{
	hwndMain = hWnd;
	hwndDlgWin = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_FUNC), hWnd, (DLGPROC)DlgFunction);
	ShowWindow(hwndDlgWin, FALSE);
}

void FunctionDialog::ShowDlgWindow()
{
	if (!hwndDlgWin) return;
	ShowWindow(hwndDlgWin, TRUE);
}

HWND FunctionDialog::GetDlgHandler()
{
	return hwndDlgWin ? hwndDlgWin : NULL;
}
//****************************


//*****************************
//Dialog function window callback
//-------------------------
BOOL CALLBACK DlgFunction(HWND hwndDlgWin, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		dmProcessor.OnInitDlg(hwndDlgWin);
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDC_ADD_FUNCTION:
			dmProcessor.AddFunction(hwndDlgWin);
			break;
		case IDC_CLEAR:
			dmProcessor.Clear();
			break;
		case ID_CONFIRM_REDRAW:
			dmProcessor.ConfirmRedraw(hwndMain);
			break;
		default: return DefWindowProc(hwndDlgWin, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwndDlgWin, &ps);
		EndPaint(hwndDlgWin, &ps);
	}
	break;
	case WM_VSCROLL:
		dmProcessor.OnVertScroll(hwndDlgWin, wParam);
		break;
	case WM_SYSCOMMAND:
		if (wParam == SC_CLOSE) ShowWindow(hwndDlgWin, FALSE);
		break;
	case WM_DESTROY:
		DestroyWindow(hwndDlgWin);
		PostQuitMessage(0);
		break;
	default: break;
	}
	return FALSE;
}
//***************************
