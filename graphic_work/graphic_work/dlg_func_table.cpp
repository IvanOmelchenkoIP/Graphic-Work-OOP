#include "framework.h"

#include <vector>
#include <string>
#include <time.h>

#include "single_func_container.h"
#include "dlg_func_table.h"

//-------------------------------------------
//ititializing table, column sizes and header
void FuncTable::InitTable(HWND hwndTableWin)
{
	RECT parentRect;
	GetClientRect(hwndTableWin, &parentRect);

	tableWidth = parentRect.right - parentRect.left;
	tableHeight = cellHeight;

	hwndTable = CreateWindowEx(NULL, L"STATIC", NULL, WS_CHILD | WS_VISIBLE, tableStartX, tableStartY, tableWidth, tableHeight, hwndTableWin, (HMENU)NULL, NULL, 0);

	SetColumnSizes();

	funcs.resize(contaierSize);
	AddFuncCell();

	//InvalidateRect(hwndTable, NULL, TRUE);
}

void FuncTable::SetColumnSizes()
{
	int colSize = tableWidth / 5;
	int nameColSize = (int)(colSize * 2.5);
	int coordColSize = (int)( (tableWidth - nameColSize) / 4 );

	cellY = tableStartY;

	inputFieldWidth = tableWidth / 4 * 3 - 5;
}

//adding rows and adjusting table to fit new ones
void FuncTable::AddFunction()
{
	if (!hwndTable) return;
	AdjustTable();

	contaierSize += 1;
	funcs.resize(contaierSize);
	AddFuncCell();
}

void FuncTable::AddFuncCell()
{
	FuncCell cell;

	cell.id = id;
	id++;

	cell.hwnd = CreateWindowEx(NULL, L"EDIT", L"Ââåä³òü ôóíêö³þ", WS_CHILD | WS_VISIBLE, inputFieldX, fieldY, tableWidth - 10, fieldHeight, hwndTable, (HMENU)NULL, NULL, 0);
	
	cell.ys = fieldY;

	srand(time(NULL));
    cell.red = rand() % (255 - 0 + 1) + 0;
    cell.green = rand() % (255 - 0 + 1) + 0;
    cell.blue = rand() % (255 - 0 + 1) + 0;

	cellY += cellHeight;
	fieldY += cellHeight;

	funcs.push_back(cell);
}

void FuncTable::AdjustTable()
{
	tableHeight += cellHeight;
	SetWindowPos(hwndTable, HWND_TOP, tableStartX, tableStartY, tableWidth, tableHeight, SWP_NOMOVE | SWP_SHOWWINDOW);
}

void FuncTable::Confirm(HWND hwndMain)
{
	fc = SingleFunctionContainer::GetInstance();
	fc->funcs.resize(funcs.size());
	fc->reds.resize(funcs.size());
	fc->greens.resize(funcs.size());
	fc->blues.resize(funcs.size());

	const unsigned int BUF_SIZE = 255;
	TCHAR tmpBuf[BUF_SIZE];
	for (int i = 1; i < funcs.size(); i++)
	{
		FuncCell cell = funcs[i];
		GetWindowText(cell.hwnd, tmpBuf, BUF_SIZE);
		std::wstring bufWstr(&tmpBuf[0]);
		std::string bufStr(bufWstr.begin(), bufWstr.end());

		funcs[i].func = bufStr;
		fc->funcs.push_back(bufStr);

		fc->reds.push_back(cell.red / 255);
		fc->greens.push_back(cell.green);
		fc->blues.push_back(cell.blue);
	}

	InvalidateRect(hwndMain, NULL, TRUE);
}

void FuncTable::Clear()
{
	funcs.empty();
	tableHeight = cellHeight;
	SetWindowPos(hwndTable, HWND_TOP, tableStartX, tableStartY, tableWidth, tableHeight, SWP_NOMOVE | SWP_SHOWWINDOW);
}