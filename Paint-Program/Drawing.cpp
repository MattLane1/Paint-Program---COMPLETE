/*
	@class CDrawing.cpp
	@purpose The purpose of this class is to handle all aspects of drawing on the window
*/

#include "stdafx.h"
#include "Drawing.h"
#include "Resource.h"

CDrawing::CDrawing()
{
}


CDrawing::~CDrawing()
{
}


void CDrawing::DrawLines(CPoint point, CChildView* pView, int iPrevX, int iPrevY, int iSelectedColour, int iLineWidth, int iDrawingStyle, CPoint savedMouseLocation)
{
	HPEN hPen;//The pen object
	//CDC MemDC;//A device context to a memory location
	CClientDC dc(pView);//A device context to the client

	SetCursor(LoadCursor(NULL, IDC_UPARROW));
	//Get the pen to used for drawing
	hPen = GetPen(iSelectedColour, iLineWidth);

	//MemDC.CreateCompatibleDC(&dc);
	SelectObject(dc, hPen);

	//Draw on the window in one of three modes
	switch (iDrawingStyle)
	{
		case FREEHAND:
			dc.MoveTo(iPrevX, iPrevY );
			dc.LineTo(point.x , point.y);
		break;

		case HORIZONTAL:
			dc.MoveTo(savedMouseLocation.x, savedMouseLocation.y);
			dc.LineTo(point.x, savedMouseLocation.y);
		break;

		case VERTICAL:
			dc.MoveTo(savedMouseLocation.x, savedMouseLocation.y);
			dc.LineTo(savedMouseLocation.x, point.y);
		break;
	}
}

/* Create the pen to be used for drawing, based on the colour selected */
HPEN CDrawing::GetPen(int iSelectedColour, int iLineWidth)
{
	HPEN hPen;

	//Create the pen with which we will draw, based on the colour chosen
	switch (iSelectedColour) 
	{
	case RED:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(255, 0, 0));
		break;

	case DARKGREEN:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(34, 177, 76));
		break;

	case DARKBLUE:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(63, 72, 204));
		break;

	case BLACK:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(0, 0, 0));
		break;

	case DARKGREY:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(127, 127, 127));
		break;

	case DARKRED:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(136, 0, 21));
		break;

	case DARKORANGE:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(255, 127, 39));
		break;

	case YELLOW:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(255, 242, 0));
		break;

	case MIDDLEBLUE:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(0, 162, 232));
		break;

	case DARKPURPLE:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(163, 73, 164));
		break;

	case WHITE:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(255, 255, 255));
		break;

	case LIGHTGREY:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(195, 195, 195));
		break;

	case BROWN:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(185, 122, 87));
		break;

	case PINK:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(255, 174, 201));
		break;

	case LIGHTORANGE:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(255, 201, 14));
		break;

	case PEACH:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(239, 228, 176));
		break;

	case LIGHTGREEN:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(181, 230, 29));
		break;

	case LIGHTBLUE:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(153, 217, 234));
		break;

	case GREYBLUE:
		hPen = CreatePen(PS_SOLID, iLineWidth, RGB(112, 146, 190));
		break;
	}
	return hPen;
}