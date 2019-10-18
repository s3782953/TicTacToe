// Co caro.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Co caro.h"


/*#ifndef NOMINMAX
#define NOMINMAX
#endif*/

#define NOMINMAX
#include <windows.h> 
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <string>
#include <vector>
#include <random>
/*
#define NOMINMAX
#define max(a,b)    (((a)>(b) ) ? (a):(b)) 
#define min(a,b)    (((a)<(b) ) ? (a):(b))
*/
#ifdef min

#undef min

#undef max

#endif

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
struct Move
{
	unsigned int x = 0;
	unsigned int y = 0;
};
Square a[3][3];
bool danhdau = true;
bool Check1 = true;
int nCurrentSelectedItem = 0;
TCHAR player1_name[128], player2_name[128];

Move getEasyAiMove();
Move minimax();
int maxSearch();
int minSearch();

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HMENU hMenu;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Name_Dlg(HWND, UINT, WPARAM, LPARAM);

void Location_BoardArr(int &iResult, int &jResult, int x, int y, RECT r);
bool CheckRow(int i, int j, int type);
bool CheckColumn(int i, int j, int type);
bool Check_1st_Diagonal_Line(int i, int j, int type);
bool Check_2nd_Diagonal_Line(int i, int j, int type);

bool Check_Tie();

void Add_Menu(HWND hWnd);
void UpdateMenuState(HWND hWnd, int newMenuItem);
void Paint_Board(HDC hdc, RECT r);
void Paint_X(int &kx, int &ky, int x_tmp, int y_tmp, RECT r, HDC dc, int i, int j);
void Paint_O(int &kx, int &ky, int x_tmp, int y_tmp, RECT r, HDC dc, int i, int j);

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
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCEW(IDC_COCARO);
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
	case WM_CREATE: {
		Add_Menu(hWnd);
		break;
	}
    case WM_COMMAND:
        {

            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_PLAYER_PLAYER:
				MessageBox(hWnd, L"YOU CHOSE PLAYER VS PLAYER MODE", L"NOTICE", MB_OK);
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Name_Dlg);
				UpdateMenuState(hWnd, ID_PLAYER_PLAYER);
				break;
			case ID_PLAYER_COMPUTER_EASY:
				MessageBox(hWnd, L"YOU CHOSE PLAYER VS COMPUTER: EASY MODE", L"NOTICE", MB_OK);
				UpdateMenuState(hWnd, ID_PLAYER_COMPUTER_EASY);
				break;
			case ID_PLAYER_COMPUTER_HARD:
				MessageBox(hWnd, L"YOU CHOSE PLAYER VS COMPUTER: HARD MODE", L"NOTICE", MB_OK);
				UpdateMenuState(hWnd, ID_PLAYER_COMPUTER_HARD);
				break;
            case IDM_ABOUT:
                //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				TCHAR msg[128];
				wsprintf(msg, L"Game Tic-tac-toe by team VN");
				MessageBox(hWnd, msg, L"About", MB_OK);
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

			Paint_Board(hdc, r);

			

			ReleaseDC(hWnd, hdc);
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
	{
		if (nCurrentSelectedItem == 556) {

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
				Paint_X(kx, ky, x_tmp, y_tmp, r, dc, i, j);
				danhdau = false;
			}
			else {
				Paint_O(kx, ky, x_tmp, y_tmp, r, dc, i, j);
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
					wsprintf(msg, L"Player 1 win: ");
					//_sntprintf(msg, 128, player1_name);
					_tcscat_s(msg, 128, player1_name);
					MessageBox(hWnd, msg, L"WINNER", MB_OK);

					PostQuitMessage(0);
					break;
				}

				if (Check_Tie() == true) {
					TCHAR msg[128];
					wsprintf(msg, L"Game Tie");
					MessageBox(hWnd, msg, L"Game Tie", MB_OK);

					PostQuitMessage(0);
				}

			}
			else {

				if (CheckRow(iTmp, jTmp, 2) == true ||
					CheckColumn(iTmp, jTmp, 2) == true ||
					Check_1st_Diagonal_Line(iTmp, jTmp, 2) == true ||
					Check_2nd_Diagonal_Line(iTmp, jTmp, 2) == true) {

					TCHAR msg[128];
					wsprintf(msg, L"Player 2 win: ");
					_tcscat_s(msg, 128, player2_name);
					MessageBox(hWnd, msg, L"WINNER", MB_OK);

					PostQuitMessage(0);
					break;
				}

				if (Check_Tie() == true) {
					TCHAR msg[128];
					wsprintf(msg, L"Game Tie");
					MessageBox(hWnd, msg, L"Game Tie", MB_OK);

					PostQuitMessage(0);
				}
			}
		}
		// easy
		if (nCurrentSelectedItem == 558) {
			
			HDC dc;
			dc = GetDC(hWnd);
			RECT r;
			GetClientRect(hWnd, &r);

			/*TCHAR msg[128];
			wsprintf(msg, L"x = %d, y = %d, r.right = %d, r.bottom = %d", x, y, r.right, r.bottom);
			MessageBox(hWnd, msg, L"Input Location", MB_OK);*/
			int x, y;

			int x_tmp,
				y_tmp;

			int i, j;

			i = 0; j = 0;
			int ky, kx;
			Move Move_tmp;

			if (danhdau == true) {
				x = LOWORD(lParam);
				y = HIWORD(lParam);

				x_tmp = x - (x % (r.right / 3));
				y_tmp = y - (y % (r.bottom / 3));

				Paint_X(kx, ky, x_tmp, y_tmp, r, dc, i, j);
				danhdau = false;
			}
			else {
				Move_tmp = getEasyAiMove();

				for (int i1 = 0; i1 < 3; i1++) {
					for (int j1 = 0; j1 < 3; j1++) {

						if (Move_tmp.x == j1 && Move_tmp.y == i1 && a[i1][j1].move == 0) {

							MoveToEx(dc, a[i1][j1].x, a[i1][j1].y, NULL);
							Ellipse(dc, a[i1][j1].x1, a[i1][j1].y1, a[i1][j1].x4, a[i1][j1].y4);
							a[i1][j1].move = 2;

						}

					}
				}
				
				danhdau = true;


			}


			int iTmp = 0, jTmp = 0;

			if (danhdau == false) {
				Location_BoardArr(iTmp, jTmp, x, y, r);
			}

			if (danhdau == false) {

				if (CheckRow(iTmp, jTmp, 1) == true ||
					CheckColumn(iTmp, jTmp, 1) == true ||
					Check_1st_Diagonal_Line(iTmp, jTmp, 1) == true ||
					Check_2nd_Diagonal_Line(iTmp, jTmp, 1) == true) {

					TCHAR msg[128];
					wsprintf(msg, L"Player win");
					MessageBox(hWnd, msg, L"WINNER", MB_OK);

					PostQuitMessage(0);
					break;
				}

				if (Check_Tie() == true) {
					TCHAR msg[128];
					wsprintf(msg, L"Game Tie");
					MessageBox(hWnd, msg, L"Game Tie", MB_OK);

					PostQuitMessage(0);
				}

			}
			else {

				if (CheckRow(Move_tmp.y, Move_tmp.x, 2) == true ||
					CheckColumn(Move_tmp.y, Move_tmp.x, 2) == true ||
					Check_1st_Diagonal_Line(Move_tmp.y, Move_tmp.x, 2) == true ||
					Check_2nd_Diagonal_Line(Move_tmp.y, Move_tmp.x, 2) == true) {

					TCHAR msg[128];
					wsprintf(msg, L"Computer win");
					MessageBox(hWnd, msg, L"WINNER", MB_OK);

					PostQuitMessage(0);
					break;
				}

				if (Check_Tie() == true) {
					TCHAR msg[128];
					wsprintf(msg, L"Game Tie");
					MessageBox(hWnd, msg, L"Game Tie", MB_OK);

					PostQuitMessage(0);
				}
			}
		}
		// hard
		if (nCurrentSelectedItem == 559) {

			HDC dc;
			dc = GetDC(hWnd);
			RECT r;
			GetClientRect(hWnd, &r);

			/*TCHAR msg[128];
			wsprintf(msg, L"x = %d, y = %d, r.right = %d, r.bottom = %d", x, y, r.right, r.bottom);
			MessageBox(hWnd, msg, L"Input Location", MB_OK);*/
			int x, y;

			int x_tmp,
				y_tmp;

			int i, j;

			i = 0; j = 0;
			int ky, kx;
			Move Move_tmp;

			if (danhdau == true) {
				x = LOWORD(lParam);
				y = HIWORD(lParam);

				x_tmp = x - (x % (r.right / 3));
				y_tmp = y - (y % (r.bottom / 3));

				Paint_X(kx, ky, x_tmp, y_tmp, r, dc, i, j);
				danhdau = false;
			}
			else {
				Move_tmp = minimax();

				for (int i1 = 0; i1 < 3; i1++) {
					for (int j1 = 0; j1 < 3; j1++) {

						if (Move_tmp.x == j1 && Move_tmp.y == i1 && a[i1][j1].move == 0) {

							MoveToEx(dc, a[i1][j1].x, a[i1][j1].y, NULL);
							Ellipse(dc, a[i1][j1].x1, a[i1][j1].y1, a[i1][j1].x4, a[i1][j1].y4);
							a[i1][j1].move = 2;

						}

					}
				}

				danhdau = true;


			}


			int iTmp = 0, jTmp = 0;

			if (danhdau == false) {
				Location_BoardArr(iTmp, jTmp, x, y, r);
			}

			if (danhdau == false) {

				if (CheckRow(iTmp, jTmp, 1) == true ||
					CheckColumn(iTmp, jTmp, 1) == true ||
					Check_1st_Diagonal_Line(iTmp, jTmp, 1) == true ||
					Check_2nd_Diagonal_Line(iTmp, jTmp, 1) == true) {

					TCHAR msg[128];
					wsprintf(msg, L"Player win");
					MessageBox(hWnd, msg, L"WINNER", MB_OK);

					PostQuitMessage(0);
					break;
				}

				if (Check_Tie() == true) {
					TCHAR msg[128];
					wsprintf(msg, L"Game Tie");
					MessageBox(hWnd, msg, L"Game Tie", MB_OK);

					PostQuitMessage(0);
				}

			}
			else {

				if (CheckRow(Move_tmp.y, Move_tmp.x, 2) == true ||
					CheckColumn(Move_tmp.y, Move_tmp.x, 2) == true ||
					Check_1st_Diagonal_Line(Move_tmp.y, Move_tmp.x, 2) == true ||
					Check_2nd_Diagonal_Line(Move_tmp.y, Move_tmp.x, 2) == true) {

					TCHAR msg[128];
					wsprintf(msg, L"Computer win");
					MessageBox(hWnd, msg, L"WINNER", MB_OK);

					PostQuitMessage(0);
					break;
				}

				if (Check_Tie() == true) {
					TCHAR msg[128];
					wsprintf(msg, L"Game Tie");
					MessageBox(hWnd, msg, L"Game Tie", MB_OK);

					PostQuitMessage(0);
				}
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
INT_PTR CALLBACK Name_Dlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
		if (LOWORD(wParam) == IDOK) {
			GetDlgItemText(hDlg, IDC_EDIT2, player1_name, 128);
			GetDlgItemText(hDlg, IDC_EDIT3, player2_name, 128);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
        break;
    }
    return (INT_PTR)FALSE;
}

void Paint_Board(HDC hdc, RECT r) {
	MoveToEx(hdc, 0, 0, NULL);

	int j = 0, x = 0, y = 0;
	int r1 = r.bottom / 3;
	int r2 = (r.bottom / 3) * 2;

	for (int i = 0; i < r.bottom; i++) {

		if (i == r1 || i == r2) {

			MoveToEx(hdc, 0, y - 1, NULL);
			LineTo(hdc, r.right, y - 1);
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
}

void Paint_X(int &kx, int &ky, int x_tmp, int y_tmp, RECT r, HDC dc, int i, int j) {
	for (ky = 0; ky < r.bottom; ky += (r.bottom / 3)) {
		for (kx = 0; kx < r.right; kx += (r.right / 3)) {


			if (a[i][j].x1 == x_tmp &&
				a[i][j].y1 == y_tmp &&
				a[i][j].move == 0) {

				MoveToEx(dc, x_tmp, y_tmp, NULL);
				LineTo(dc, x_tmp + (r.right / 3), y_tmp + (r.bottom / 3));
				MoveToEx(dc, x_tmp, y_tmp + (r.bottom / 3), NULL);
				LineTo(dc, x_tmp + (r.right / 3), y_tmp);

				a[i][j].move = 1;

			}

			j++;
		}
		i++;
		j = 0;
	}
}
void Paint_O(int &kx, int &ky, int x_tmp, int y_tmp, RECT r, HDC dc, int i, int j) {
	for (ky = 0; ky < r.bottom; ky += (r.bottom / 3)) {
		for (kx = 0; kx < r.right; kx += (r.right / 3)) {


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

bool Check_Tie() {
	int counter = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (a[i][j].move != 0) {
				counter++;
			}
		}
	}
	if (counter == 9) return true;
}

bool Check_win(int player_type) {
	for (unsigned int i = 0; i < 3; i++)
	{
		// Check horizontals
		if (a[i][0].move == player_type && a[i][1].move == player_type && a[i][2].move == player_type)
			return true;

		// Check verticals
		if (a[0][i].move == player_type && a[1][i].move == player_type && a[2][i].move == player_type)
			return true;
	}

	// Check diagonals
	if (a[0][0].move == player_type && a[1][1].move == player_type && a[2][2].move == player_type)
		return true;

	if (a[0][2].move == player_type && a[1][1].move == player_type && a[2][0].move == player_type)
		return true;

	return false;
}

void Add_Menu(HWND hWnd) {

	hMenu = CreateMenu();

	HMENU hOptionMenu = CreateMenu();

	AppendMenu(hOptionMenu, MF_STRING, ID_PLAYER_PLAYER, L"Player vs Player Mode");
	AppendMenu(hOptionMenu, MF_STRING, ID_PLAYER_COMPUTER_EASY, L"Player Vs Computer: Easy Mode");
	AppendMenu(hOptionMenu, MF_STRING, ID_PLAYER_COMPUTER_HARD, L"Player Vs Computer: Hard Mode");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hOptionMenu, L"Options");
	AppendMenu(hMenu, MF_STRING, IDM_EXIT, L"Exit");
	AppendMenu(hMenu, MF_STRING, IDM_ABOUT, L"About");


	SetMenu(hWnd, hMenu);
}

void UpdateMenuState(HWND hWnd, int newMenuItem)
{
	//HMENU hDraw = GetSubMenu(GetMenu(hWnd), 1); // get handle of Draw menu pop-up
												//uncheck current selected item
	HMENU hDraw = GetMenu(hWnd);
	CheckMenuItem(hDraw, nCurrentSelectedItem, MF_UNCHECKED | MF_BYCOMMAND);
	CheckMenuItem(hDraw, newMenuItem, MF_CHECKED | MF_BYCOMMAND);
	nCurrentSelectedItem = newMenuItem;


}

Move getEasyAiMove()
{
	std::vector<Move> freePositions;
	Move freePos, move;
	Move temp;

	for (unsigned int i = 0; i < 3; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			if (a[i][j].move == 0)
			{
				freePos.y = i;
				freePos.x = j;
				freePositions.push_back(freePos);
			}
		}
	}

	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(freePositions), std::end(freePositions), rng);
	temp = freePositions.front();

	move.x = temp.x;
	move.y = temp.y;

	return move;
}

int minSearch()
{
	if (Check_win(1))
	{
		return 10;
	}
	else if (Check_win(2))
	{
		return -10;
	}
	else if (Check_Tie())
	{
		return 0;
	}

	int score = std::numeric_limits<int>::max();

	for (unsigned int i = 0; i < 3; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			if (a[i][j].move == 0)
			{
				a[i][j].move = 2;
				score = std::min(score, maxSearch());
				a[i][j].move = 0;
			}
		}
	}

	return score;
}
int maxSearch()
{
	if (Check_win(1))
	{
		return 10;
	}
	else if (Check_win(2))
	{
		return -10;
	}
	else if (Check_Tie())
	{
		return 0;
	}

	int score = std::numeric_limits<int>::min();

	for (unsigned int i = 0; i < 3; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			if (a[i][j].move == 0)
			{
				a[i][j].move = 1;
				score = std::max(score, minSearch());
				a[i][j].move = 0;
			}
		}
	}

	return score;
}

Move minimax()
{
	int score = std::numeric_limits<int>::max();
	Move move;

	for (unsigned int i = 0; i < 3; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			if (a[i][j].move == 0)
			{
				a[i][j].move = 2;

				int temp = maxSearch();

				if (temp < score)
				{
					score = temp;
					move.x = j;
					move.y = i;
				}
				a[i][j].move = 0;
			}
		}
	}

	return move;
}