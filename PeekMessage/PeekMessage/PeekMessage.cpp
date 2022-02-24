// PeekMessage.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "PeekMessage.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;
HDC g_hDC;
bool g_bLoop = true;
RECT g_tPlayerRect = { 100,100, 200,200 };

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

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PEEKMESSAGE));

    MSG msg;

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
	if (GetAsyncKeyState('D') & 0x8000)
	{
		g_tPlayerRect.left += 1;
		g_tPlayerRect.right += 1;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		g_tPlayerRect.left -= 1;
		g_tPlayerRect.right -= 1;
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		g_tPlayerRect.top -= 1;
		g_tPlayerRect.bottom -= 1;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		g_tPlayerRect.top += 1;
		g_tPlayerRect.bottom += 1;
	}
	
	
	CheckSide();

	Rectangle(g_hDC, g_tPlayerRect.left, g_tPlayerRect.top, g_tPlayerRect.right, g_tPlayerRect.bottom);
}

void CheckSide()
{
	if (g_tPlayerRect.top <= 0)
	{
		g_tPlayerRect.top += 1;
		g_tPlayerRect.bottom += 1;
	}
	else if (g_tPlayerRect.bottom >= 600)
	{
		g_tPlayerRect.top -= 1;
		g_tPlayerRect.bottom -= 1;
	}

	if (g_tPlayerRect.left <= 0)
	{
		g_tPlayerRect.left += 1;
		g_tPlayerRect.right += 1;
	}
	else if (g_tPlayerRect.right >= 800)
	{
		g_tPlayerRect.left -= 1;
		g_tPlayerRect.right -= 1;
	}
}
