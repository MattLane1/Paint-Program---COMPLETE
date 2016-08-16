
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Paint-Program.h"
#include "ChildView.h"
#include "Drawing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView
CChildView::CChildView()
{
	tme.cbSize = NULL;
	iSelectedColour = RED;
	iLineWidth = 1;
	m_iDrawingStyle = FREEHAND;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}


/* The mouse has moved within the window. This could denote drawing, or it could not. */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	//We do not need to re-do this for every pixel the mouse moves. Only once when it enters the window. When it leaves, we clear the size
	//as a flag so we know it has left. 
	if (tme.cbSize == NULL)
	{
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		tme.dwHoverTime = 1;
		_TrackMouseEvent(&tme);
	}

	//When we leave the drawing area, we set the previous position information to NULL, so that we dont try drawing from where the mouse left the window
	//To where it returned. This would create odd straight lines for no reason. If we did just leave and return, get the new position before proceeding. 
	if (iPrevX != NULL && iPrevY != NULL)
	{
		//Check if the mouse button is being held down. We only draw if the user is holding down the button!
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)//Button is down
		{
			//Create a pointer to the drawing class
			CDrawing* pDraw = new CDrawing();

			//Pass the mouse coordinates to the drawing function
			pDraw->DrawLines(point, this, iPrevX, iPrevY, iSelectedColour, iLineWidth, m_iDrawingStyle, savedMouseLocation);

			//Save the current position, then draw a line from it, to the new position, when the mouse moved. This connects the dots that would otherwise be created.
			iPrevX = point.x;
			iPrevY = point.y;
		}
	}
	else
	{//Save the new position information
		iPrevX = point.x;
		iPrevY = point.y;
	}

	if ((GetKeyState(VK_LBUTTON) & 0x100) == 0)//Button is up
	{
		iPrevX = point.x;
		iPrevY = point.y;
	}

	CWnd::OnMouseMove(nFlags, point);
}


/* The mouse has left the drawing area */
void CChildView::OnMouseLeave()
{
	//Reset the tracker
	tme.cbSize = NULL;

	//There is no previous position data, because we are outside the window
	iPrevX = NULL;
	iPrevY = NULL;

	CWnd::OnMouseLeave();
}

/* The mouse button is down */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//Create a pointer to the drawing class
	CDrawing* pDraw = new CDrawing();

	//Save where we are now, so we can stay on one row or column
	savedMouseLocation = point;

	//Pass the mouse coordinates to the drawing function
	pDraw->DrawLines(point, this, iPrevX, iPrevY, iSelectedColour, iLineWidth, m_iDrawingStyle, savedMouseLocation);

	CWnd::OnLButtonDown(nFlags, point);
}
