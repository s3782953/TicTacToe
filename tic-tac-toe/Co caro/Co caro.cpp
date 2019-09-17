// Co caro.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Co caro.h"

#define MAX_LOADSTRING 100

struct Square {
	// Location of center point
	int x;
	int y;

	// Locations of 4 points from 4 peaks
	int x1 , x2 , x3 , x4 ;
	int y1 , y2 , y3 , y4 ; 

	int move = 0;
};
Square a[3][3];
bool danhdau = true;
bool Check1 = true;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Location_BoardArr(int &iResult, int &jResult, int x, int y, RECT r);
bool CheckRow(int i, int j, int type);
bool CheckColumn(int i, int j, int type);
bool Check_1st_Diagonal_Line(int i, int j, int type);
bool Check_2nd_Diagonal_Line(int i, int j, int type);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COCARO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COCARO));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COCARO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_COCARO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
            // TODO: Add any drawing code that uses hdc here...

			RECT r;
			GetClientRect(hWnd, &r);

			MoveToEx(hdc, 0, 0, NULL);

			int j = 0, x = 0, y = 0;
			int r1 = r.bottom / 3;
			int r2 = (r.bottom / 3) * 2;

			for (int i = 0; i < r.bottom; i++) {

				if (i == r1 || i == r2) {

					MoveToEx(hdc, 0, y - 1, NULL);
					LineTo(hdc, r.right, y-1);
					MoveToEx(hdc, 0, y - 1, NULL);
					MoveToEx(hdc, 0, y, NULL);
					LineTo(hdc, r.right, y);
					MoveToEx(hdc, 0, y, NULL);
					MoveToEx(hdc, 0, y + 1, NULL);
					LineTo(hdc, r.right, y + 1);
					MoveToEx(hdc, 0, y + 1, NULL);
				}
				y++;
			}

			MoveToEx(hdc, 0, 0, NULL);

			j = 0; x = 0; y = 0;
			int b1 = r.right / 3;
			int b2 = (r.right / 3) * 2;

			for (int i = 0; i < r.right; i++) {

				if (i == b1 || i == b2) {

					MoveToEx(hdc, x - 1, 0, NULL);
					LineTo(hdc, x - 1, r.bottom);
					MoveToEx(hdc, x - 1, 0, NULL);
					MoveToEx(hdc, x, 0, NULL);
					LineTo(hdc, x, r.bottom);
					MoveToEx(hdc, x, 0, NULL);
					MoveToEx(hdc, x + 1, 0, NULL);
					LineTo(hdc, x + 1, r.bottom);
					MoveToEx(hdc, x + 1, 0, NULL);

				}
				x++;
			}

			MoveToEx(hdc, 0, 0, NULL);

			int i = 0; j = 0;
			
			/*for (i = 0; i < 3; i++) {
				for (j = 0; j < 3; j++) {
					if (a[i][j].move != 0) {
						Check1 = false;
						break;
					}
				}
			}*/

			//if (Check1 == true) {
				for (y = ((r.bottom / 3) / 2); y < r.bottom; y += (r.bottom / 3)) {
					for (x = ((r.right / 3) / 2); x < r.right; x += (r.right / 3)) {

						// Center point
						a[i][j].x = x;
						a[i][j].y = y;

						a[i][j].x1 = a[i][j].x - ((r.right / 3) / 2);
						a[i][j].x2 = a[i][j].x + ((r.right / 3) / 2);
						a[i][j].x3 = a[i][j].x - ((r.right / 3) / 2);
						a[i][j].x4 = a[i][j].x + ((r.right / 3) / 2);

						a[i][j].y1 = a[i][j].y - ((r.bottom / 3) / 2);
						a[i][j].y2 = a[i][j].y - ((r.bottom / 3) / 2);
						a[i][j].y3 = a[i][j].y + ((r.bottom / 3) / 2);
						a[i][j].y4 = a[i][j].y + ((r.bottom / 3) / 2);

						a[i][j].move = 0;
						j++;
					}
					i++;
					j = 0;
				}
			//}
			/*else {
				i = 0; j = 0;

				for (i = 0; i < 3; i++) {
					for (j = 0; j < 3; j++) {

						if (a[i][j].move == 1) {

							MoveToEx(hdc, a[i][j].x1, a[i][j].y1, NULL);
							LineTo(hdc, a[i][j].x1 + (r.right / 3), a[i][j].y1 + (r.bottom / 3));
							MoveToEx(hdc, a[i][j].x1, a[i][j].y1 + (r.bottom / 3), NULL);
							LineTo(hdc, a[i][j].x1 + (r.right / 3), a[i][j].y1);

						}
						else {
							if (a[i][j].move == 2) {

								MoveToEx(hdc, a[i][j].x, a[i][j].y, NULL);
								Ellipse(hdc, a[i][j].x1, a[i][j].y1, a[i][j].x4, a[i][j].y4);

							}
						}
					}
				}
			}*/


			ReleaseDC(hWnd, hdc);
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
	{
		int x, y;
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		HDC dc;
		dc = GetDC(hWnd);
		RECT r;
		GetClientRect(hWnd, &r);

		/*TCHAR msg[128];
		wsprintf(msg, L"x = %d, y = %d, r.right = %d, r.bottom = %d", x, y, r.right, r.bottom);
		MessageBox(hWnd, msg, L"Input Location", MB_OK);*/

		int x_tmp = x - (x % (r.right / 3)),
			y_tmp = y - (y % (r.bottom / 3));

		int i, j;

		i = 0; j = 0;
		int ky, kx;

		if (danhdau == true) {

			for (ky = 0; ky < r.bottom; ky += (r.bottom/3)) {
				for (kx = 0; kx < r.right; kx += (r.right/3)) {


					if (a[i][j].x1 == x_tmp && 
						a[i][j].y1 == y_tmp && 
						a[i][j].move == 0) {

						MoveToEx(dc, x_tmp, y_tmp, NULL);
						LineTo(dc, x_tmp + (r.right/3), y_tmp + (r.bottom/3));
						MoveToEx(dc, x_tmp, y_tmp + (r.bottom/3), NULL);
						LineTo(dc, x_tmp + (r.right/3), y_tmp);

						a[i][j].move = 1;

					}

					j++;
				}
				i++;
				j = 0;
			}
			danhdau = false;

		}
		else {

			for (ky = 0; ky < r.bottom; ky += (r.bottom/3)) {
				for (kx = 0; kx < r.right; kx += (r.right/3)) {


					if (a[i][j].x1 == x_tmp && a[i][j].y1 == y_tmp && a[i][j].move == 0) {
						MoveToEx(dc, a[i][j].x, a[i][j].y, NULL);

						Ellipse(dc, a[i][j].x1, a[i][j].y1, a[i][j].x4, a[i][j].y4);

						a[i][j].move = 2;

					}
					j++;
				}
				i++;
				j = 0;
			}
			danhdau = true;

		}


		int iTmp = 0, jTmp = 0;
		Location_BoardArr(iTmp, jTmp, x, y, r);

		if (danhdau == false) {

			if (CheckRow(iTmp, jTmp, 1) == true ||
				CheckColumn(iTmp, jTmp, 1) == true ||
				Check_1st_Diagonal_Line(iTmp, jTmp, 1) == true ||
				Check_2nd_Diagonal_Line(iTmp, jTmp, 1) == true) {

				TCHAR msg[128];
				wsprintf(msg, L"Player 1 win");
				MessageBox(hWnd, msg, L"WINNER", MB_OK);

				PostQuitMessage(0);
				break;
			}
		}
		else {

			if (CheckRow(iTmp, jTmp, 2) == true ||
				CheckColumn(iTmp, jTmp, 2) == true ||
				Check_1st_Diagonal_Line(iTmp, jTmp, 2) == true ||
				Check_2nd_Diagonal_Line(iTmp, jTmp, 2) == true) {

				TCHAR msg[128];
				wsprintf(msg, L"Player 2 win");
				MessageBox(hWnd, msg, L"WINNER", MB_OK);

				PostQuitMessage(0);
				break;
			}
		}
		

		break;
	}
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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

void Location_BoardArr(int &iResult, int &jResult, int x, int y, RECT r) {

	int x_tmp = x - (x % (r.right / 3)),
		y_tmp = y - (y % (r.bottom / 3));

	int i, j;
	i = 0; j = 0;
	int kx, ky;

	for (ky = 0; ky < r.bottom; ky += (r.bottom / 3)) {
		for (kx = 0; kx < r.right; kx += (r.right / 3)) {

			if (a[i][j].x1 == x_tmp && a[i][j].y1 == y_tmp && a[i][j].move != 0) {

				iResult = i;
				jResult = j;
				return;
			}
			j++;
		}
		i++;
		j = 0;
	}
}

bool CheckRow(int i, int j, int type) {
	
	if (j == 0) {
		if (a[i][j + 1].move == type && 
			a[i][j + 2].move == type) {
			return true;
		}
		else return false;
	}
	else {
		if (j == 1) {
			if (a[i][j + 1].move == type && 
				a[i][j - 1].move == type) {
				return true;
			}
			else return false;
		} else {
			if (j == 2) {
				if (a[i][j - 1].move == type &&
					a[i][j - 2].move == type) {
					return true;
				}
				else return false;
			}
		}
	}
}
bool CheckColumn(int i, int j, int type) {
	if (i == 0) {
		if (a[i + 1][j].move == type &&
			a[i + 2][j].move == type) {
			return true;
		}
		else return false;
	}
	else {
		if (i == 1) {
			if (a[i + 1][j].move == type &&
				a[i - 1][j].move == type) {
				return true;
			}
			else return false;
		}
		else {
			if (i == 2) {
				if (a[i - 1][j].move == type &&
					a[i - 2][j].move == type) {
					return true;
				}
				else return false;
			}
		}
	}
}
bool Check_1st_Diagonal_Line(int i, int j, int type) {
	if (i == 0 && j == 0) {
		if (a[1][1].move == type && a[2][2].move == type) {
			return true;
		}
		else return false;
	}
	else {
		if (i == 1 && j == 1) {
			if (a[0][0].move == type && a[2][2].move == type) {
				return true;
			}
			else return false;
		}
		else {
			if (i == 2 && j == 2) {
				if (a[1][1].move == type && a[0][0].move == type) {
					return true;
				}
				else return false;
			}
		}
	}
}
bool Check_2nd_Diagonal_Line(int i, int j, int type) {

	if (i == 0 && j == 2) {
		if (a[1][1].move == type && a[2][0].move == type) {
			return true;
		}
		else return false;
	}
	else {
		if (i == 1 && j == 1) {
			if (a[0][2].move == type && a[2][0].move == type) {
				return true;
			}
			else return false;
		}
		else {
			if (i == 2 && j == 0) {
				if (a[1][1].move == type && a[0][2].move == type) {
					return true;
				}
				else return false;
			}
		}
	}
}
