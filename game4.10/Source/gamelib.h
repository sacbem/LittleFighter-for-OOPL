#define SIZE_X				 800//990		
#define SIZE_Y				 600//640		
#define OPEN_AS_FULLSCREEN	 true		
#define SHOW_LOAD_PROGRESS   true		
#define DEFAULT_BG_COLOR	 RGB(0,0,0)	
#define GAME_CYCLE_TIME		 10		    
#define SHOW_GAME_CYCLE_TIME false		
#define ENABLE_GAME_PAUSE	 true		
#define ENABLE_AUDIO		 true		

enum GAME_STATES {
	GAME_STATE_INIT,
	GAME_STATE_RUN,
	GAME_STATE_OVER
};

/////////////////////////////////////////////////////////////////////////////
// Header for STL (Standard Template Library)
/////////////////////////////////////////////////////////////////////////////

#include <list>
#include <string>
#include <vector>
#include <map>
using namespace std;


#define GAME_ASSERT(boolexp,str)											\
		if (!(boolexp)) {													\
			int id;															\
			char s[300]="";													\
			sprintf(s,"Game fatal error:\n\n%s\n\nFile: %s\n\nLine: %d"		\
				"\n\n(Press Retry to debug the application, "				\
				"if it is executed in debug mode.)"							\
				"\n(Press Cancel otherwise.)",								\
				 str , __FILE__,__LINE__);									\
			id = AfxMessageBox(s, MB_RETRYCANCEL);							\
			if (id == IDCANCEL)												\
				exit(1);													\
			AfxDebugBreak();												\
		}

namespace game_framework {

class CSpecialEffect {
public:
	static void  SetCurrentTime();					
	static DWORD GetEllipseTime();					
	static int   GetCurrentTimeCount();				
	static void  Delay(DWORD ms);					
	static void  DelayFromSetCurrentTime(DWORD ms);	
private:
	static DWORD ctime;
	static int	 ctimeCount;
};

class CDDraw {
	friend class CMovingBitmap;
public:
	~CDDraw();
	static void  BltBackColor(DWORD);		
	static void  BltBackToPrimary();		
	static CDC*  GetBackCDC();				
	static void  GetClientRect(CRect &r);	
	static void  Init(int, int);			
	static void  ReleaseBackCDC();			
	static bool  SetFullScreen(bool);		
	static bool  IsFullScreen();			
private:
	CDDraw();								// private constructor
	static void  BltBitmapToBack(unsigned SurfaceID, int x, int y);
	static void  BltBitmapToBack(unsigned SurfaceID, int x, int y, double factor);
	static void  BltBitmapToBitmap(unsigned SourceID, unsigned TargetID, int x, int y);
	static void	 CheckDDFail(char *s);
	static bool  CreateSurface();
	static bool  CreateSurfaceFullScreen();
	static bool  CreateSurfaceWindowed();
	static void  LoadBitmap(int i, int IDB_BITMAP);
	static void  LoadBitmap(int i, char *filename);
	static DWORD MatchColorKey(LPDIRECTDRAWSURFACE lpDDSurface, COLORREF color);
	static int   RegisterBitmap(int IDB_BITMAP, COLORREF ColorKey);
	static int   RegisterBitmap(char *filename, COLORREF ColorKey);
	static void  ReleaseSurface();
	static void  RestoreSurface();
	static void  SetColorKey(unsigned SurfaceID, COLORREF color);
	static HDC					hdc;
	static CDC					cdc;
	static CView				*pCView;
	static LPDIRECTDRAW2		lpDD;
	static LPDIRECTDRAWCLIPPER	lpClipperPrimary;   
	static LPDIRECTDRAWCLIPPER	lpClipperBack;   
	static LPDIRECTDRAWSURFACE	lpDDSPrimary;
	static LPDIRECTDRAWSURFACE	lpDDSBack;
	static vector<LPDIRECTDRAWSURFACE>	lpDDS;
	static HRESULT				ddrval;
	static vector<int>			BitmapID;
	static vector<string>		BitmapName;
	static vector<CRect>		BitmapRect;
	static vector<COLORREF>		BitmapColorKey;
	static bool					fullscreen;
	static CDDraw				ddraw;
	static int					size_x, size_y;
};

class CMovingBitmap {
public:
	CMovingBitmap();
	int   Height();						
	int   Left();						
	void  LoadBitmap(int,COLORREF=CLR_INVALID);		
	void  LoadBitmap(char *,COLORREF=CLR_INVALID);	
	void  SetTopLeft(int,int);			
	void  ShowBitmap();					
	void  ShowBitmap(double factor);	
	void  ShowBitmap(CMovingBitmap &);	
	int   Top();						
	int   Width();						
protected:
	CRect    location;			// location of the bitmap
	bool     isBitmapLoaded;	// whether a bitmap has been loaded
	unsigned SurfaceID;			// the surface id of this bitmap
};

class CAnimation {
public:
	CAnimation(int=10);				
	void  AddBitmap(int,COLORREF=CLR_INVALID);
									
	void  AddBitmap(char *,COLORREF=CLR_INVALID);
									
	int   GetCurrentBitmapNumber();	
	int   Height();					
	bool  IsFinalBitmap();			
	int   Left();					
	void  OnMove();					
	void  OnShow();					
	void  Reset();					
	void  SetDelayCount(int);		
	void  SetTopLeft(int,int);		
	int   Top();					
	int   Width();					
private:
	list<CMovingBitmap>				bmp;			// list of CMovingBitmap
	list<CMovingBitmap>::iterator	bmp_iter;		// list iterator
	int								bmp_counter;	
	int								delay_counter;	
	int								delay_count;	
	int								x, y;			
};

class CInteger {
public:
	CInteger(int=5);			// default 5 digits
	void Add(int n);			
	int  GetInteger();			
	void LoadBitmap();			
	void SetInteger(int);		
	void SetTopLeft(int,int);	
	void ShowBitmap();			
private:
	const int NUMDIGITS;			
	static CMovingBitmap digit[11]; 
	int x, y;						
	int n;							
	bool isBmpLoaded;				
};


class CGame;
class CGameStateInit;
class CGameStateRun;
class CGameStateOver;


class CGameState {
public:
	CGameState(CGame *g);
	void OnDraw();			// Template Method
	void OnCycle();			// Template Method

	virtual ~CGameState() {}								// virtual destructor
	virtual void OnBeginState() {}							
	virtual void OnInit() {}								
	virtual void OnKeyDown(UINT, UINT, UINT) {}				
	virtual void OnKeyUp(UINT, UINT, UINT) {}				
	virtual void OnLButtonDown(UINT nFlags, CPoint point) {}
	virtual void OnLButtonUp(UINT nFlags, CPoint point) {}	
	virtual void OnMouseMove(UINT nFlags, CPoint point) {}  
	virtual void OnRButtonDown(UINT nFlags, CPoint point) {}
	virtual void OnRButtonUp(UINT nFlags, CPoint point) {}	
protected:
	void GotoGameState(int state);							
	void ShowInitProgress(int percent);						
	
	virtual void OnMove() {}								
	virtual void OnShow() = 0;								
	CGame *game;
};

class CGame {
public:
	CGame();										
	~CGame();										
	bool IsRunning();								
	void OnDraw();									
	void OnFilePause();								
	void OnInit();									
	void OnInitStates();							
	bool OnIdle();									
	void OnKeyDown(UINT, UINT, UINT);				
	void OnKeyUp(UINT, UINT, UINT);					
	void OnKillFocus();								
	void OnLButtonDown(UINT nFlags, CPoint point);	
	void OnLButtonUp(UINT nFlags, CPoint point);	
	void OnMouseMove(UINT nFlags, CPoint point);   
	void OnRButtonDown(UINT nFlags, CPoint point);	
	void OnRButtonUp(UINT nFlags, CPoint point);	
	void OnResume();								
	void OnSetFocus();								
	void OnSuspend();								
	void SetGameState(int);
	static CGame *Instance();
	//static int SelectCharacterID[2];
	static int selectCharacterID[2];
	static int totalDamage[2];
	static bool isEnd;
	static bool isEndRun;
	static bool isWin;
private:
	bool			running;			
	bool            suspended;			
	const int		NUM_GAME_STATES;	
	CGameState		*gameState;			
	CGameState		*gameStateTable[3];	
	static CGame	instance;			
	
};

//class DataForm {
//public:
//
//};
}