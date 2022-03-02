// PeekMessage.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "PeekMessage.h"
#include <list>
#include <random>
#include <cmath>

using namespace std;

#define MAX_LOADSTRING 100

typedef struct _tagSphere
{
	float x, y;
	float r;
}SPHERE, *PSPHERE;

typedef struct _tagRectangle
{
	float l, t, r, b;
}RECTANGLE, *PRECTANGLE;

typedef struct _tagMonster
{
	SPHERE tSphere;
	float fSpeed;
	float fTime;
	float fLimitTime;
	int iDir;
}MONSTER, *PMONSTER;

typedef struct _tagBullet
{
	SPHERE rc;
	float fDist;
	float fLimitDist;
	float fLimitTime;
}BULLET, *PBULLET;



// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;
HDC g_hDC;
bool g_bLoop = true;
RECTANGLE g_tPlayerRect = { 100,100, 200,200 };
MONSTER g_tMonster;

LARGE_INTEGER g_tSecond;
LARGE_INTEGER g_tTime;
float g_fDeltaTime;
bool bEnemyCheck = false;

list<BULLET> g_PlayerBulletList;
list<BULLET> g_EnemyBulletList;

enum MOVE_DIR
{
	MD_BACK = -1,
	MD_NONE,
	MD_FRONT = 1
};


// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void Run();
void CheckSide();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PEEKMESSAGE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	g_hDC = GetDC(g_hWnd);

	//몬스터 초기화
	g_tMonster.tSphere.x = 800.f - 50.f;
	g_tMonster.tSphere.y = 50.f;
	g_tMonster.tSphere.r = 50.f;
	g_tMonster.fSpeed = 300.f;
	g_tMonster.fTime = 0.0f;
	g_tMonster.fLimitTime = 2.0f;
	g_tMonster.iDir = MD_NONE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PEEKMESSAGE));

    MSG msg;

	QueryPerformanceFrequency(&g_tSecond);
	QueryPerformanceCounter(&g_tTime);

    // 기본 메시지 루프입니다.
    while (g_bLoop)
    {
        if (PeekMessage(&msg, nullptr, 0,0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			//여기서 게임 개발
			static int iCount;
			++iCount;
			if (iCount == 10000)
			{
				iCount = 0;
				Run();
			}

		}
    }

	ReleaseDC(g_hWnd, g_hDC);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PEEKMESSAGE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   RECT  rc = { 0, 0, 800, 600 };
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   SetWindowPos(hWnd, HWND_TOPMOST,100,100,rc.right-rc.left, rc.bottom-rc.top, SWP_NOMOVE | SWP_NOZORDER );


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		g_bLoop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void Run()
{
	LARGE_INTEGER tTime;

	
	QueryPerformanceCounter(&tTime);
	g_fDeltaTime = (tTime.QuadPart - g_tTime.QuadPart) / (float)g_tSecond.QuadPart;
	g_tTime = tTime;

	//타임 스케일을 통하여 전체적인 게임 속도를 조정할수 있다.
	static float fTimeScale = 1.f;

	if (GetAsyncKeyState(VK_F1) & 0x8000)
	{
		fTimeScale -= g_fDeltaTime;
		if (fTimeScale < 0.f)
		{
			fTimeScale = 0.f;
		}
	}

	if (GetAsyncKeyState(VK_F2) & 0x8000)
	{
		fTimeScale += g_fDeltaTime;
		if (fTimeScale > 1.f)
		{
			fTimeScale = 1.f;
		}
	}
	
	//플레이어 초당 이동속도 500
	float fSpeed = 500 * g_fDeltaTime * fTimeScale;

	if (GetAsyncKeyState('D') & 0x8000)
	{
		g_tPlayerRect.l += fSpeed;
		g_tPlayerRect.r += fSpeed;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		g_tPlayerRect.l -= fSpeed;
		g_tPlayerRect.r -= fSpeed;
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		g_tPlayerRect.t -= fSpeed;
		g_tPlayerRect.b -= fSpeed;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		g_tPlayerRect.t += fSpeed;
		g_tPlayerRect.b += fSpeed;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		BULLET rcBullet;
		rcBullet.rc.x = g_tPlayerRect.r + 50.f;
		rcBullet.rc.y = g_tPlayerRect.t + 50.f;
		rcBullet.rc.r = 25.f;
		rcBullet.fDist = 0.f;
		rcBullet.fLimitDist = 800.0f;

		g_PlayerBulletList.push_back(rcBullet);
	}
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		POINT ptMouse;

		GetCursorPos(&ptMouse);

		ScreenToClient(g_hWnd, &ptMouse);

		if (g_tPlayerRect.l <= ptMouse.x && g_tPlayerRect.r >= ptMouse.x
			&& g_tPlayerRect.t <= ptMouse.y && g_tPlayerRect.b >= ptMouse.y)
		{
			MessageBox(NULL, L"플레이어 클릭", L"마우스 클릭", MB_OK);
		}

		float fMX = g_tMonster.tSphere.x - ptMouse.x;
		float fMY = g_tMonster.tSphere.y - ptMouse.y;
		float fMDist = sqrtf(fMX * fMX + fMY * fMY);

		if (g_tMonster.tSphere.r >= fMDist)
		{
			MessageBox(NULL, L"몬스터 클릭", L"마우스 클릭", MB_OK);
		}
	}
	
	list<BULLET>::iterator iter;
	list<BULLET>::iterator iterEnd = g_PlayerBulletList.end();

	g_tMonster.tSphere.y += g_tMonster.fSpeed * g_fDeltaTime * g_tMonster.iDir;
	//g_tMonster.tRC.b += g_tMonster.fSpeed * g_fDeltaTime * g_tMonster.iDir;

	if (g_tMonster.tSphere.y + g_tMonster.tSphere.r >= 600)
	{
		g_tMonster.iDir = MD_BACK;
		g_tMonster.tSphere.y = 550;
	}
	else if (g_tMonster.tSphere.y - g_tMonster.tSphere.r <= 0)
	{
		g_tMonster.iDir = MD_FRONT;
		g_tMonster.tSphere.y = 50;
	}

	fSpeed = 600.f * g_fDeltaTime * fTimeScale;

	for (iter = g_PlayerBulletList.begin(); iter != iterEnd;)
	{
		(*iter).rc.x += fSpeed;
		(*iter).fDist += fSpeed;

		float fX = (*iter).rc.x - g_tMonster.tSphere.x;
		float fY = (*iter).rc.y - g_tMonster.tSphere.y;

		float fDist = sqrtf(fX*fX + fY*fY);

		if (fDist <= (*iter).rc.r + g_tMonster.tSphere.r)
		{
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}
		else if ((*iter).fDist >= (*iter).fLimitDist)
		{
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}
		else if (800 <= (*iter).rc.x - (*iter).rc.r)
		{
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}
		else
		{
			++iter;
		}
	}

	for (iter = g_PlayerBulletList.begin(); iter != iterEnd; ++iter)
	{
		Ellipse(g_hDC, (*iter).rc.x - (*iter).rc.r,
			(*iter).rc.y - (*iter).rc.r,
			(*iter).rc.x + (*iter).rc.r,
			(*iter).rc.y + (*iter).rc.r);
	}

	fSpeed = 500.f * g_fDeltaTime * fTimeScale;
	
	
	CheckSide();

	g_tMonster.fTime += g_fDeltaTime;

	if (g_tMonster.fTime >= g_tMonster.fLimitTime)
	{
		g_tMonster.fTime -= g_tMonster.fLimitTime;

		BULLET tBullet = {};
		tBullet.rc.x = g_tMonster.tSphere.x - g_tMonster.tSphere.r - 25.f;
		tBullet.rc.y = g_tMonster.tSphere.y;
		tBullet.rc.r = 25.f;
		tBullet.fDist = 0.f;
		tBullet.fLimitDist = 800.0f;

		g_EnemyBulletList.push_back(tBullet);
	}


	iterEnd = g_EnemyBulletList.end();

	for (iter = g_EnemyBulletList.begin(); iter != iterEnd;)
	{
		(*iter).rc.x -= fSpeed;
		(*iter).fDist += fSpeed;

		if ((*iter).fDist >= (*iter).fLimitDist)
		{
			iter = g_EnemyBulletList.erase(iter);
			iterEnd = g_EnemyBulletList.end();
		}
		else if (0 >= (*iter).rc.x + (*iter).rc.r)
		{
			iter = g_EnemyBulletList.erase(iter);
			iterEnd = g_EnemyBulletList.end();
		}
		//else if (g_tPlayerRect.l <= (*iter).rc.r && (*iter).rc.l <= g_tPlayerRect.r &&
		//	g_tPlayerRect.t <= (*iter).rc.b && (*iter).rc.t <= g_tPlayerRect.b)
		//{
		//	iter = g_EnemyBulletList.erase(iter);
		//	iterEnd = g_EnemyBulletList.end();
		//}
		else
		{
			++iter;
		}
	}

	for (iter = g_EnemyBulletList.begin(); iter != iterEnd; ++iter)
	{
		Ellipse(g_hDC, (*iter).rc.x - (*iter).rc.r, 
			(*iter).rc.y - (*iter).rc.r, 
			(*iter).rc.x + (*iter).rc.r,
			(*iter).rc.y + (*iter).rc.r);
	}

	Ellipse(g_hDC, g_tMonster.tSphere.x-g_tMonster.tSphere.r, g_tMonster.tSphere.y - g_tMonster.tSphere.r, g_tMonster.tSphere.x + g_tMonster.tSphere.r, g_tMonster.tSphere.y + g_tMonster.tSphere.r);
	Rectangle(g_hDC, g_tPlayerRect.l , g_tPlayerRect.t, g_tPlayerRect.r, g_tPlayerRect.b);
}

void CheckSide()
{
	RECT rcWindow;
	GetClientRect(g_hWnd, &rcWindow);

	//플레이어 충돌 처리
	if (g_tPlayerRect.t <= 0)
	{
		g_tPlayerRect.t = 0;
		g_tPlayerRect.b = 100;
	}
	else if (g_tPlayerRect.b >= rcWindow.bottom)
	{
		g_tPlayerRect.t = rcWindow.bottom - 100;
		g_tPlayerRect.b  = rcWindow.bottom;
	}

	if (g_tPlayerRect.l <= 0)
	{
		g_tPlayerRect.l = 0;
		g_tPlayerRect.r = 100;
	}
	else if (g_tPlayerRect.r >= rcWindow.right)
	{
		g_tPlayerRect.l = rcWindow.right - 100;
		g_tPlayerRect.r = rcWindow.right;
	}

}
