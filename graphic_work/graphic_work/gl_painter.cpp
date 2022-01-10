#include "framework.h"
#include "glut.h"

#include <string>
#include <map>
#include <vector>
#include <math.h>

#include "parser_char_types.h"
#include "parser_equation.h"
#include "single_func_container.h"
#include "gl_painter.h"

void GlDrawer::Resize(GLsizei width, GLsizei height) {
	if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, width, height);
}

void GlDrawer::OnInit() {
	//SetWindowPixelFormat(hdc);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

// код функции, которая устанавливает параметры контекста воспроизведения OpenGL. 
void GlDrawer::SetWindowPixelFormat(HDC hDC)
{
	int m_GLPixelIndex;
	PIXELFORMATDESCRIPTOR pfd;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;

	pfd.cColorBits = 255 * 255 * 255;
	pfd.cRedBits = 255;
	pfd.cRedShift = 255;
	pfd.cGreenBits = 255;
	pfd.cGreenShift = 255;
	pfd.cBlueBits = 255;
	pfd.cBlueShift = 255;

	pfd.cAlphaBits = 0;
	pfd.cAlphaShift = 0;
	pfd.cAccumBits = 255 * 255 * 255;
	pfd.cAccumRedBits = 255;
	pfd.cAccumGreenBits = 255;
	pfd.cAccumBlueBits = 255;
	pfd.cAccumAlphaBits = 255;
	pfd.cDepthBits = 255;
	pfd.cStencilBits = 255;

	m_GLPixelIndex = ChoosePixelFormat(hDC, &pfd);
	DescribePixelFormat(hDC, m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
	SetPixelFormat(hDC, m_GLPixelIndex, &pfd);
}


void GlDrawer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, 1, 3, -3);
	gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
	DrawAxis();

	glPopMatrix();
	DrawGraphics();

	SwapBuffers(wglGetCurrentDC());
}
void GlDrawer::DrawAxis() // Отрисовка осей
{
	glColor3d(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();
	glColor3d(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glColor3d(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

void GlDrawer::DrawGraphics() // Отрисовка модели
{
	fc = SingleFunctionContainer::GetInstance();
	if (!fc->funcs.size()) return;

	for (int i = 1; i < fc->funcs.size(); i++)
	{
		std::string func = fc->funcs[i];

		ep = new ExpressionParser;

		GLdouble red = (double)((double)1 * (double)fc->reds[i] / (double)255);
		GLdouble green = (double)((double)1 * (double)fc->blues[i] / (double)255);
		GLdouble blue = (double)((double)1 * (double)fc->greens[i] / (double)255);

		glColor3d(red, green, blue);
		glBegin(GL_POLYGON);

		ep->EvaluateToVertexes(func);

		glEnd();

		delete ep;

	}

}
