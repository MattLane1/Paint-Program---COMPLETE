#pragma once
#include "ChildView.h"

// CControls dialog

class CControls : public CDialogEx
{
	DECLARE_DYNAMIC(CControls)

public:
	CControls(CWnd* pParent, CChildView* pView);   // standard constructor
	virtual ~CControls();

	// Dialog Data
	enum { IDD = IDD_CONTROLS };

	//Save class pointer to pass colour information
	CChildView* m_pView;

	//Set and get slider information
	CSliderCtrl m_LineWidth;

	//Freehand, or straight lines
	int iDrawingStyle;

	//Attach the colours to their button objects
	void LoadColourTable();

	//A dc to the window
	CDC* dC;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedColourRed();
	afx_msg void OnBnClickedColourDarkGreen();
	afx_msg void OnBnClickedColourLightGreen();
	afx_msg void OnBnClickedColourDarkBlue();
	afx_msg void OnBnClickedColourLightBlue();
	afx_msg void OnBnClickedColourDarkPurple();
	afx_msg void OnBnClickedColourDarkRed();
	afx_msg void OnBnClickedColourGreyBlue();
	afx_msg void OnBnClickedColourDarkGrey();
	afx_msg void OnBnClickedColourLightGrey();
	afx_msg void OnBnClickedColourDarkOrange();
	afx_msg void OnBnClickedColourLightOrange();
	afx_msg void OnBnClickedColourMiddleBlue();
	afx_msg void OnBnClickedColourPink();
	afx_msg void OnBnClickedColourLightPeach();
	afx_msg void OnBnClickedColourYellow();
	afx_msg void OnBnClickedColourWhite();
	afx_msg void OnBnClickedColourBlack();
	afx_msg void OnNMCustomdrawSliderThickness(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadioFreehand();
	afx_msg void OnBnClickedRadioHorizontal();
	afx_msg void OnBnClickedRadioVertical();
	afx_msg void OnBnClickedButtonEraser();
};
