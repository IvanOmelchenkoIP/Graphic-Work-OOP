#pragma once

class GlDrawer {
private:
	SingleFunctionContainer* fc;
	ExpressionParser* ep;

	void DrawAxis(); 
	void DrawGraphics(); 

public:
	void SetWindowPixelFormat(HDC hDC);
	void OnInit();

	void Resize(GLsizei width, GLsizei height);
	void Draw();
};
