#pragma once
class FunctionDialog
{
private:
	HWND hwndDlgWin;

public:
	void InitDlg(HWND, HINSTANCE);
	void ShowDlgWindow();
	HWND GetDlgHandler();
};
