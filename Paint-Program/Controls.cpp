/*
   @Class Controls.cpp
   @Purpose This class is connected to the dialog box the user uses to select colours, line styles etc. When a button is pressed, 
   a coorsponding function is called in this class.

*/

#include "stdafx.h"
#include "Paint-Program.h"
#include "Controls.h"
#include "afxdialogex.h"
#include "FileStorage.h"

// CControls dialog
IMPLEMENT_DYNAMIC(CControls, CDialogEx)

CControls::CControls(CWnd* pParent, CChildView* pView)
	: CDialogEx(IDD, pParent)
{
	//Save the class pointer to CChildView so we can pass the selected colour information
	m_pView = pView;
}

/* Destructor */
CControls::~CControls()
{
}

void CControls::DoDataExchange(CDataExchange* pDX)
{
	//Display the colour options
	LoadColourTable();

	//Set up the line width slider
	DDX_Control(pDX, IDC_SLIDER_THICKNESS, m_LineWidth);
	m_LineWidth.SetRange(1, 80, true);
	m_LineWidth.SetPos(1);

	//Set the default radio button for line direction (Freehand)
	CButton* pButton = (CButton*)GetDlgItem(IDC_RADIO_FREEHAND);
	pButton->SetCheck(true);

	CDialogEx::DoDataExchange(pDX);
}

/* Message Map */
BEGIN_MESSAGE_MAP(CControls, CDialogEx)
	ON_BN_CLICKED(IDC_COLOUR_RED, &CControls::OnBnClickedColourRed)
	ON_BN_CLICKED(IDC_COLOUR_DARK_GREEN, &CControls::OnBnClickedColourDarkGreen)
	ON_BN_CLICKED(IDC_COLOUR_LIGHT_GREEN, &CControls::OnBnClickedColourLightGreen)
	ON_BN_CLICKED(IDC_COLOUR_DARK_BLUE, &CControls::OnBnClickedColourDarkBlue)
	ON_BN_CLICKED(IDC_COLOUR_LIGHT_BLUE, &CControls::OnBnClickedColourLightBlue)
	ON_BN_CLICKED(IDC_COLOUR_DARK_PURPLE, &CControls::OnBnClickedColourDarkPurple)
	ON_BN_CLICKED(IDC_COLOUR_DARK_RED, &CControls::OnBnClickedColourDarkRed)
	ON_BN_CLICKED(IDC_COLOUR_GREY_BLUE, &CControls::OnBnClickedColourGreyBlue)
	ON_BN_CLICKED(IDC_COLOUR_DARK_GREY, &CControls::OnBnClickedColourDarkGrey)
	ON_BN_CLICKED(IDC_COLOUR_LIGHT_GREY, &CControls::OnBnClickedColourLightGrey)
	ON_BN_CLICKED(IDC_COLOUR_DARK_ORANGE, &CControls::OnBnClickedColourDarkOrange)
	ON_BN_CLICKED(IDC_COLOUR_LIGHT_ORANGE, &CControls::OnBnClickedColourLightOrange)
	ON_BN_CLICKED(IDC_COLOUR_MIDDLE_BLUE, &CControls::OnBnClickedColourMiddleBlue)
	ON_BN_CLICKED(IDC_COLOUR_PINK, &CControls::OnBnClickedColourPink)
	ON_BN_CLICKED(IDC_COLOUR_LIGHT_PEACH, &CControls::OnBnClickedColourLightPeach)
	ON_BN_CLICKED(IDC_COLOUR_YELLOW, &CControls::OnBnClickedColourYellow)
	ON_BN_CLICKED(IDC_COLOUR_WHITE, &CControls::OnBnClickedColourWhite)
	ON_BN_CLICKED(IDC_COLOUR_BLACK, &CControls::OnBnClickedColourBlack)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_THICKNESS, &CControls::OnNMCustomdrawSliderThickness)
	ON_BN_CLICKED(IDC_RADIO_FREEHAND, &CControls::OnBnClickedRadioFreehand)
	ON_BN_CLICKED(IDC_RADIO_HORIZONTAL, &CControls::OnBnClickedRadioHorizontal)
	ON_BN_CLICKED(IDC_RADIO_VERTICAL, &CControls::OnBnClickedRadioVertical)
	ON_BN_CLICKED(IDC_BUTTON_ERASER, &CControls::OnBnClickedButtonEraser)
END_MESSAGE_MAP()

/* Methods */

/* This function loads all the bitmaps needed for the colour table in the dialog, and connects them to each button*/
void CControls::LoadColourTable()
{
	CBitmap bmp;
	CButton* pButton;

	//Attach all the colours to the respective buttons
	//The resource lists the colours from 300 - 317, the buttons run 1000 - 1017. So by looping and adding 700, we attach the colour to it's button. 
	for (int attach = 300; attach <= 317; attach++)
	{
		bmp.LoadBitmapW(attach);
		pButton = (CButton*)GetDlgItem((attach + 700));
		pButton->ModifyStyle(0, BS_BITMAP);
		pButton->SetBitmap(bmp);
		bmp.DeleteObject();
	}
}

// CControls message handlers

/* Set the thickness of the line to be drawn*/
void CControls::OnNMCustomdrawSliderThickness(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	m_pView->iLineWidth = m_LineWidth.GetPos();

	*pResult = 0;
}

/*How should the lines be drawn? Freehand, or straight lines?*/
void CControls::OnBnClickedRadioFreehand()
{
	m_pView->m_iDrawingStyle = FREEHAND;
}

/* Set the line to draw straight, horizontally */
void CControls::OnBnClickedRadioHorizontal()
{
	m_pView->m_iDrawingStyle = HORIZONTAL;
}

/* set the line to draw straight, vertically */
void CControls::OnBnClickedRadioVertical()
{
	m_pView->m_iDrawingStyle = VERTICAL;
}

/* 
Colour selection section: 
When a colour is selected from the controls dialog, the 
coorosponding selection function is called here. 
*/

void CControls::OnBnClickedColourRed()
{
	m_pView->iSelectedColour = RED;
}

void CControls::OnBnClickedColourDarkGreen()
{
	m_pView->iSelectedColour = DARKGREEN;
}


void CControls::OnBnClickedColourLightGreen()
{
	m_pView->iSelectedColour = LIGHTGREEN;
}


void CControls::OnBnClickedColourDarkBlue()
{
	m_pView->iSelectedColour = DARKBLUE;
}


void CControls::OnBnClickedColourLightBlue()
{
	m_pView->iSelectedColour = LIGHTBLUE;
}


void CControls::OnBnClickedColourDarkPurple()
{
	m_pView->iSelectedColour = DARKPURPLE;
}


void CControls::OnBnClickedColourDarkRed()
{
	m_pView->iSelectedColour = DARKRED;
}


void CControls::OnBnClickedColourGreyBlue()
{
	m_pView->iSelectedColour = GREYBLUE;
}


void CControls::OnBnClickedColourDarkGrey()
{
	m_pView->iSelectedColour = DARKGREY;
}


void CControls::OnBnClickedColourLightGrey()
{
	m_pView->iSelectedColour = LIGHTGREY;
}


void CControls::OnBnClickedColourDarkOrange()
{
	m_pView->iSelectedColour = DARKORANGE;
}


void CControls::OnBnClickedColourLightOrange()
{
	m_pView->iSelectedColour = LIGHTORANGE;
}


void CControls::OnBnClickedColourMiddleBlue()
{
	m_pView->iSelectedColour = MIDDLEBLUE;
}


void CControls::OnBnClickedColourPink()
{
	m_pView->iSelectedColour = PINK;
}


void CControls::OnBnClickedColourLightPeach()
{
	m_pView->iSelectedColour = PEACH;
}


void CControls::OnBnClickedColourYellow()
{
	m_pView->iSelectedColour = YELLOW;
}


void CControls::OnBnClickedColourWhite()
{
	m_pView->iSelectedColour = WHITE;
}


void CControls::OnBnClickedColourBlack()
{
	m_pView->iSelectedColour = BLACK;
}

void CControls::OnBnClickedButtonEraser()
{
	m_pView->iSelectedColour = WHITE;
}
