/*
	@Class CMainFrame
	@Purpose This class is the starting point of the program. It creates the frame and client area there in which will be used for drawing. 
	It also is called when the menu at the top of the window is used. Things like save and load. 
*/

#include "stdafx.h"
#include "Paint-Program.h"
#include "FileStorage.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_FILE_SAVE, &CMainFrame::OnFileSave)
	ON_COMMAND(ID_FILE_LOAD, &CMainFrame::OnFileLoad)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_FILE_NEW, &CMainFrame::OnFileNew)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

}

CMainFrame::~CMainFrame()
{
}

// Called when the window is created
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect clientRect;
	CRect positionRect;
	CRect toolboxRect;

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	/* Create the toolbox the user can use to pick colours, line styles, etc. */
	m_pControls = new CControls(this, &m_wndView);
	bool b = m_pControls->Create(CControls::IDD);

	//Get the dimentions of the window
	GetClientRect(&clientRect);
	m_pControls->GetWindowRect(toolboxRect);

	//Relate the coordinates to the screen as a whole, so spot 0, 0 of the rect is the top left corner of the drawing area, not the desktop.
	ClientToScreen(&clientRect);

	//Position the toolbox dialog beside the window
	positionRect.top = (clientRect.top - 45);
	positionRect.left = clientRect.right;
	positionRect.bottom = (clientRect.bottom );
	positionRect.right = (clientRect.right + toolboxRect.Width());
	m_pControls->MoveWindow(positionRect, 1);

	//Display the toolbox dialog
	m_pControls->ShowWindow(true);

	CDC* dc = GetDC();
	m_pControls->dC = dc;

	//Pass a pointer to our controls dialog to the childview class, so it can use it to keep the dialog box beside the window.
	//m_wndView.m_pControls = m_pControls;

	return 0;
}

/*Called just as the window is made, set the style of the window*/
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

/* Pass the windows messages */
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

/* The user wants to save the image */
void CMainFrame::OnFileSave()
{
	//Create a pointer to the CFileStorage class
	CFileStorage* pStore = new CFileStorage();
	CRect clientRect;

	//Get a rect of the window, based on the desktop coordinates.
	GetClientRect(&clientRect);
	ClientToScreen(&clientRect);

	//Pass the coordinates, and a DC to the window, so we know what we are saving and where from
	pStore->SaveFile(GetDC(), clientRect);
}

/* The user wants to load an image */
void CMainFrame::OnFileLoad()
{
	//Create a pointer to the CFileStorage class
	CFileStorage* pStore = new CFileStorage();

	//Pass a DC to the window, so we know where to display the image
	pStore->LoadFile(GetDC());
}

/* Allow the user to create a new white surface to draw on */
void CMainFrame::OnFileNew()
{
	int result = MessageBox(L"This will erase the screen and create a new surface. Are you sure?", L"Erase the screen?", MB_OKCANCEL);

	//The user selected Yes
	if (result == 1)
	{
		CRect clientRect;
		GetClientRect(&clientRect);
		CClientDC DC(&m_wndView);

		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

		SelectObject(DC, hPen);

		for (int a = clientRect.left; a <= clientRect.right; a++) {
			DC.MoveTo(a, clientRect.top);
			DC.LineTo(a, clientRect.bottom);
		}
	}
}
