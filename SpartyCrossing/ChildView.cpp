
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "SpartyCrossing.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"
#include "Item.h"
#include "Game.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Gdiplus;

/// Frame duration in milliseconds
const int FrameDuration = 30;

// CChildView
CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_LEVEL_LEVEL5, &CChildView::OnLevelLevel5)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_LEVEL_LEVEL2, &CChildView::OnLevelLevel2)
	ON_COMMAND(ID_LEVEL_LEVEL3, &CChildView::OnLevelLevel3)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_LEVEL_LEVEL0, &CChildView::OnLevelLevel0)
	ON_COMMAND(ID_CHEATS_ROADCHEAT, &CChildView::OnCheatsRoadcheat)
	ON_COMMAND(ID_CHEATS_RIVERCHEAT, &CChildView::OnCheatsRivercheat)
	ON_COMMAND(ID_CHEATS_WOLVERINECHEAT, &CChildView::OnCheatsWolverinecheat)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/**  CChildView paint function
*/
void CChildView::OnPaint() 
{
	// TODO: Add your message handler code here

	CPaintDC paintDC(this);
	CDoubleBufferDC dc(&paintDC); // device context for painting

	Graphics graphics(dc.m_hDC);

	CRect rect;
	GetClientRect(&rect);

	mGame.OnDraw(&graphics, rect.Width(), rect.Height());
	
	// Do not call CWnd::OnPaint() for painting messages

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
 * Initialize the elapsed time system
 */
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}
	/*
 * Compute the elapsed time since the last draw
 */
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	mGame.Update(elapsed);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point);

	vector<double> mousePos = mGame.OnLButtonDown(point.x, point.y);

	mGame.InteractWithItem(mousePos[0]-32, mousePos[1]-32);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) 
	{
	case VK_UP:
	case 'E':
		mGame.MoveHeroUp();
		break;
	case VK_LEFT:
	case 'S':
		mGame.MoveHeroLeft();
		break;

	case VK_DOWN:
	case 'D':
		mGame.MoveHeroDown();
		break;
	case VK_RIGHT:
	case 'F':
		mGame.MoveHeroRight();
		break;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


//Level0
void CChildView::OnLevelLevel0()
{
	mGame.NewGame(0);
}


//Level1
void CChildView::OnLevelLevel5()
{
	mGame.NewGame(1);
}

//Level2
void CChildView::OnLevelLevel2()
{
	mGame.NewGame(2);
}

//Level3
void CChildView::OnLevelLevel3()
{
	mGame.NewGame(3);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return false;
}




void CChildView::OnCheatsRoadcheat()
{
	mGame.RoadCheat();
}


void CChildView::OnCheatsRivercheat()
{
	mGame.RiverCheat();
}


void CChildView::OnCheatsWolverinecheat()
{
	mGame.WolverineCheat();
}
