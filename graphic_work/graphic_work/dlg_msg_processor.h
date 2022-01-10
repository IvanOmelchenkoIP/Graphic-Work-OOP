#pragma once

static class DlgMsgProcessor
{
private:
	FuncTable fnTable;
	SCROLLINFO si;

	int DRAWING_STATE;

	int curY = 0;
	int scrollY = 0;

	void SetPosition(HWND);
	void SetInitScrollInfo(HWND);
	
public:
	void OnInitDlg(HWND);

	void OnVertScroll(HWND, WPARAM);

	void AddFunction(HWND hwndDlgWin);
	void Clear();
	void ConfirmRedraw(HWND);
};

