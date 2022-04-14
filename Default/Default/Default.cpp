// Default.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Default.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_DEFAULT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULT));

    MSG msg;

    // 기본 메시지 루프입니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
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
   RECT rc{ 0, 0, 800, 600 };

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

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
RECT rc{ 300,300,400,400 };

enum e_Dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct Bullet
{
	e_Dir m_Dir;
	RECT m_RC;

	Bullet()
	{
	}

	Bullet(e_Dir eDir, RECT tRC)
	{
		m_Dir = eDir;
		m_RC = tRC;
	}
};

static list<Bullet*> bullet;

void DeleteList()
{
	list<Bullet*>::iterator iter;
	list<Bullet*>::iterator iterEnd = bullet.end();

	for (iter = bullet.begin(); iter != iterEnd; ++iter)
	{
		delete (*iter);
	}

	bullet.empty();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		SetTimer(hWnd, 0, 0, 0);
		break;

	case WM_TIMER:
		InvalidateRect(hWnd, 0, true);
		break;
    
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
            
			//MoveToEx(hdc, 500, 500, nullptr);
			//LineTo(hdc, 100, 200);
			//LineTo(hdc, 200, 200);
			//LineTo(hdc, 200, 100);
			//LineTo(hdc, 100, 100);

			//Rectangle(hdc, 100, 100, 200, 200);
			//Ellipse(hdc, 300, 300, 400, 400);

			for (int i = 0; i < 360; ++i)
			{
				SetPixel(hdc, 100 + int(sin(i*PI / 180) * 20), 100 + int(cos(i*PI / 180) * 20), BLACK_BRUSH);
			}

			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
			
			if (!bullet.empty())
			{
				list<Bullet*>::iterator iter;
				list<Bullet*>::iterator iterEnd = bullet.end();

				for (iter = bullet.begin(); iter != iterEnd; ++iter)
				{
					Ellipse(hdc, (*iter)->m_RC.left, (*iter)->m_RC.top, (*iter)->m_RC.right, (*iter)->m_RC.bottom);
					
					if ((*iter)->m_Dir == UP)
					{
						(*iter)->m_RC.bottom -= 10;
						(*iter)->m_RC.top -= 10;
					}
					else if ((*iter)->m_Dir == DOWN)
					{
						(*iter)->m_RC.bottom += 10;
						(*iter)->m_RC.top += 10;
					}
					else if ((*iter)->m_Dir == LEFT)
					{
						(*iter)->m_RC.left -= 10;
						(*iter)->m_RC.right -= 10;
					}
					else
					{
						(*iter)->m_RC.left += 10;
						(*iter)->m_RC.right += 10;
					}

				}
			}

			EndPaint(hWnd, &ps);
        }
        break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_DOWN:
			bullet.push_back(new Bullet(DOWN, rc));
			break;

		case VK_UP:
			bullet.push_back(new Bullet(UP, rc));
			break;
		
		case VK_LEFT:
			bullet.push_back(new Bullet(LEFT, rc));
			break;
		
		case VK_RIGHT:
			bullet.push_back(new Bullet(RIGHT, rc));
			break;
			
		//case VK_SPACE:
		//	bullet.push_back(new RECT(rc));
		//	break;

		case VK_ESCAPE:
			DeleteList();
			KillTimer(hWnd, 0);
			PostQuitMessage(0);
			break;
		}
		break;

    case WM_DESTROY:
		DeleteList();
		KillTimer(hWnd, 0);
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

