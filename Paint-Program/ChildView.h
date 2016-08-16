// ChildView.h : interface of the CChildView class
//
#pragma once

// CChildView window
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	// Selected Colour
	int iSelectedColour;

	//Drawing style, Freehand or Straight lines
	int m_iDrawingStyle;

	// width of the line to be drawn
	int iLineWidth;

private:
	// Past mouse locations 
	int	iPrevY;
	int	iPrevX;

	//Saved point locations so we can force horizonal or vertical lines
	CPoint savedMouseLocation;

	//Check if the mouse leaves the window
	TRACKMOUSEEVENT tme;

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
};

