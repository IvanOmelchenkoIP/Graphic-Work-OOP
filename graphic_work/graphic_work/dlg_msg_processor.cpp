#include "framework.h"

#include <vector>
#include <string>
#include <time.h>

#include "single_func_container.h"
#include "dlg_func_table.h"
#include "dlg_msg_processor.h"

//***************************
// Function dialog message processor methods 
//***************************
// On initializing dialog
//-----------------------------
void DlgMsgProcessor::OnInitDlg(HWND hwndDlgWin)
{
	SetPosition(hwndDlgWin);
	SetInitScrollInfo(hwndDlgWin);

	fnTable.InitTable(hwndDlgWin);
}

void DlgMsgProcessor::SetPosition(HWND hwndDlgWin)
{
	POINT screenSize;
	screenSize.x = GetSystemMetrics(SM_CXSCREEN);
	screenSize.y = GetSystemMetrics(SM_CYSCREEN);

	long xs = screenSize.x / 4 * 3;
	long ys = screenSize.y / 8;
	long width = screenSize.x / 4;
	long height = screenSize.y / 8 * 5;

	MoveWindow(hwndDlgWin, xs, ys, width, height, TRUE);
}

void DlgMsgProcessor::SetInitScrollInfo(HWND hwndDlgWin)
{
	RECT rc;
	GetClientRect(hwndDlgWin, &rc);

	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = 30 * 120;
	si.nPage = (rc.bottom - rc.top);
	si.nPos = 0;
	si.nTrackPos = 0;
	SetScrollInfo((HWND)hwndDlgWin, SB_VERT, &si, true);
}
//-------------------------

// Scrolling window
void DlgMsgProcessor::OnVertScroll(HWND hwndDlgWin, WPARAM wParam)
{
	WPARAM action = LOWORD(wParam);
	switch (action)
	{
	case SB_THUMBPOSITION: case SB_THUMBTRACK:
		curY = HIWORD(wParam);
		break;
	case SB_LINEDOWN:
		curY = scrollY + 30;
		break;
	case SB_LINEUP:
		curY = scrollY - 30;
		break;
	}
	if (curY < 0) return;

	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_POS;
	si.nPos = curY;
	si.nTrackPos = 0;

	SetScrollInfo(HWND(hwndDlgWin), SB_VERT, &si, true);

	ScrollWindow(hwndDlgWin, 0, -(si.nPos - scrollY), NULL, NULL);
	UpdateWindow(hwndDlgWin);

	scrollY = curY;
}
//----------------------------

// Working with input data
//----------------------------
void DlgMsgProcessor::AddFunction(HWND hwndDlgWin)
{
	fnTable.AddFunction();
	//InvalidateRect(hwndDlgWin, NULL, TRUE);
}

void DlgMsgProcessor::Clear()
{
	fnTable.Clear();
}

void DlgMsgProcessor::ConfirmRedraw(HWND hwndMain)
{
	fnTable.Confirm(hwndMain);
}
//----------------------------