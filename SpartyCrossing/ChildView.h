
// ChildView.h : interface of the CChildView class
//

#pragma once
#include "Game.h"

/**
 *  ChildView window
 */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();
	bool mFirstDraw = true;		///< Bool for if this is first draw
	long long mLastTime = 0;    ///< Last time we read the timer
	double mTimeFreq = 0;       ///< Rate the timer updates
// Attributes
public:

// Operations
public:

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
private:
	/// The game instance being played
	CGame mGame;
public:
	/** Command for when the Left Mouse button is pressed
	  * \param nFlags Throw exception
	  * \param point The point where cursor is
	  */
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	/// Command for updating the timer in the UI
	/// \param nIDEvent The event
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	/// Command for when a key is pressed
	/// \param nChar The character pressed
	/// \param nRepCnt The repition count
	/// \param nFlags Throw expection
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	/// Command for instantiating new Level
	afx_msg void OnLevelLevel5();
	/// Command for instantiating new Level
	afx_msg void OnLevelLevel2();
	/// Command for instantiating new Level
	afx_msg void OnLevelLevel3();
	/// Command for instantiating new Level
	afx_msg void OnLevelLevel0();

	/** Command for erasing the background
	  * \param pDC The object that will redraw the background
	  * \return bool value
	  */
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	/// Command for creating road cheats
	afx_msg void OnCheatsRoadcheat();
	/// Command for creating road cheats
	afx_msg void OnCheatsRivercheat();
	/// Command for creating wolverine cheats
	afx_msg void OnCheatsWolverinecheat();
};

