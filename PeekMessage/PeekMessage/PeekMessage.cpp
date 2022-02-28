// PeekMessage.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
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
	RECTANGLE tRC;
	float fSpeed;
	float fTime;
	float fLimitTime;
	int iDir;
}MONSTER, *PMONSTER;

typedef struct _tagBullet
{
	RECTANGLE rc;
	float fDist;
	float fLimitDist;
	float fLimitTime;
}BULLET, *PBULLET;



// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
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


// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PEEKMESSAGE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	g_hDC = GetDC(g_hWnd);

	//���� �ʱ�ȭ
	g_tMonster.tRC.l = 800.f - 100.f;
	g_tMonster.tRC.t = 0.f;
	g_tMonster.tRC.r = 800.f;
	g_tMonster.tRC.b = 100.f;
	g_tMonster.fSpeed = 300.f;
	g_tMonster.fTime = 0.0f;
	g_tMonster.fLimitTime = 2.0f;
	g_tMonster.iDir = MD_NONE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PEEKMESSAGE));

    MSG msg;

	QueryPerformanceFrequency(&g_tSecond);
	QueryPerformanceCounter(&g_tTime);

    // �⺻ �޽��� �����Դϴ�.
    while (g_bLoop)
    {
        if (PeekMessage(&msg, nullptr, 0,0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		else
		{
			//���⼭ ���� ����
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
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
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
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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

	//Ÿ�� �������� ���Ͽ� ��ü���� ���� �ӵ��� �����Ҽ� �ִ�.
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
	
	//�÷��̾� �ʴ� �̵��ӵ� 500
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
		rcBullet.rc.r = g_tPlayerRect.r;
		rcBullet.rc.l = g_tPlayerRect.r + 50.0;
		rcBullet.rc.t = (g_tPlayerRect.t + g_tPlayerRect.b) / 2.0 - 25.0;
		rcBullet.rc.b = g_tPlayerRect.t + 50.0;
		rcBullet.fDist = 0.f;
		rcBullet.fLimitDist = 800.0f;

		g_PlayerBulletList.push_back(rcBullet);
	}
	
	list<BULLET>::iterator iter;
	list<BULLET>::iterator iterEnd = g_PlayerBulletList.end();

	g_tMonster.tRC.t += g_tMonster.fSpeed * g_fDeltaTime * g_tMonster.iDir;
	g_tMonster.tRC.b += g_tMonster.fSpeed * g_fDeltaTime * g_tMonster.iDir;

	if (g_tMonster.tRC.b >= 600)
	{
		g_tMonster.iDir = MD_BACK;
		g_tMonster.tRC.b = 600;
		g_tMonster.tRC.t = 500;
	}
	else if (g_tMonster.tRC.t <= 0)
	{
		g_tMonster.iDir = MD_FRONT;
		g_tMonster.tRC.b = 100;
		g_tMonster.tRC.t = 0;
	}

	fSpeed = 600.f * g_fDeltaTime * fTimeScale;

	for (iter = g_PlayerBulletList.begin(); iter != iterEnd;)
	{
		(*iter).rc.l += fSpeed;
		(*iter).rc.r += fSpeed;

		if ((*iter).fDist >= (*iter).fLimitDist)
		{
			iter = g_PlayerBulletList.erase(iter);
			iterEnd = g_PlayerBulletList.end();
		}
		else if (800 <= (*iter).rc.l)
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
		Rectangle(g_hDC, (*iter).rc.l, (*iter).rc.t, (*iter).rc.r, (*iter).rc.b);
	}

	fSpeed = 500.f * g_fDeltaTime * fTimeScale;
	
	
	CheckSide();

	g_tMonster.fTime += g_fDeltaTime;

	if (g_tMonster.fTime >= g_tMonster.fLimitTime)
	{
		g_tMonster.fTime -= g_tMonster.fLimitTime;

		BULLET tBullet = {};
		tBullet.rc.r = g_tMonster.tRC.l;
		tBullet.rc.l = g_tMonster.tRC.l - 50.0;
		tBullet.rc.t = (g_tMonster.tRC.t + g_tMonster.tRC.b) / 2.f - 25.f;
		tBullet.rc.b = g_tMonster.tRC.t + 50.0;
		tBullet.fDist = 0.f;
		tBullet.fLimitDist = 800.0f;

		g_EnemyBulletList.push_back(tBullet);
	}


	iterEnd = g_EnemyBulletList.end();

	for (iter = g_EnemyBulletList.begin(); iter != iterEnd;)
	{
		(*iter).rc.l -= fSpeed;
		(*iter).rc.r -= fSpeed;

		if ((*iter).fDist >= (*iter).fLimitDist)
		{
			iter = g_EnemyBulletList.erase(iter);
			iterEnd = g_EnemyBulletList.end();
		}
		else if (0 >= (*iter).rc.r)
		{
			iter = g_EnemyBulletList.erase(iter);
			iterEnd = g_EnemyBulletList.end();
		}
		else if (g_tPlayerRect.l <= (*iter).rc.r && (*iter).rc.l <= g_tPlayerRect.r &&
			g_tPlayerRect.t <= (*iter).rc.b && (*iter).rc.t <= g_tPlayerRect.b)
		{
			iter = g_EnemyBulletList.erase(iter);
			iterEnd = g_EnemyBulletList.end();
		}
		else
		{
			++iter;
		}
	}

	for (iter = g_EnemyBulletList.begin(); iter != iterEnd; ++iter)
	{
		Rectangle(g_hDC, (*iter).rc.l, (*iter).rc.t, (*iter).rc.r, (*iter).rc.b);
	}


	


	Rectangle(g_hDC, g_tMonster.tRC.l, g_tMonster.tRC.t, g_tMonster.tRC.r, g_tMonster.tRC.b);
	Rectangle(g_hDC, g_tPlayerRect.l , g_tPlayerRect.t, g_tPlayerRect.r, g_tPlayerRect.b);
}

void CheckSide()
{
	RECT rcWindow;
	GetClientRect(g_hWnd, &rcWindow);

	//�÷��̾� �浹 ó��
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
