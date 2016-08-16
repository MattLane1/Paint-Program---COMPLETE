#pragma once
#include "ChildView.h"


class CDrawing
{
public:
	CDrawing();
	~CDrawing();
	void DrawLines(CPoint point, CChildView* pView, int iPrevX, int iPrevY, int iSelectedColour, int iLineWidth, int iDrawingStyle, CPoint savedMouseLocation);

	HPEN GetPen(int iSelectedColour, int iLineWidth);


};

