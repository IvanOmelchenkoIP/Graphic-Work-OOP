#pragma once

typedef struct FuncCell {
	HWND hwnd;
	int id;
	std::string func;

	int ys;

	int red;
	int green;
	int blue;

} FuncCell;

class FuncTable 
{
private:
	HWND hwndTable;

	SingleFunctionContainer* fc;

	std::vector<FuncCell> funcs;
	
	int contaierSize = 1;

	int id = 0;

	const long cellHeight = 30;

	const long tableStartX = 0;
	const long tableStartY = 0;
	long tableWidth;
	long tableHeight;

	//start y coords
	long cellY = 0; //for a whole cell
	long fieldY = 5; //for a field

	long fieldHeight = 20;

	const long inputFieldX = 5;
	long inputFieldWidth;


	void SetColumnSizes();

	void AdjustTable();
	void AddFuncCell();

public:
	void InitTable(HWND);

	void AddFunction();
	void Clear();

	void Confirm(HWND);
};

